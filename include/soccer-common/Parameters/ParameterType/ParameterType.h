#ifndef PARAMETERTYPE_H
#define PARAMETERTYPE_H

#include <set>
#include <QString>
#include <QTextStream>
#include <boost/bimap.hpp>
#include <QRegularExpression>
#include "soccer-common/Utils/Utils.h"
#include "soccer-common/MagicEnum/MagicEnum.h"

namespace Parameters {
  namespace InputType {
    static constexpr const char* Text = "Text";
    static constexpr const char* SpinBox = "SpinBox";
    static constexpr const char* Slider = "Slider";
    static constexpr const char* DoubleSpinBox = "DoubleSpinBox";
    static constexpr const char* ComboBox = "ComboBox";
    static constexpr const char* CheckBox = "CheckBox";
  } // namespace InputType

  namespace Detail {
    static constexpr const char* Value = "Value";
    static constexpr const char* InputType = "InputType";
    static constexpr const char* Type = "Type";
    static constexpr const char* Description = "Description";
    static constexpr const char* MinValue = "MinValue";
    static constexpr const char* MaxValue = "MaxValue";
    static constexpr const char* Precision = "Precision";
    static constexpr const char* Options = "Options";
    static constexpr const char* Regex = "Regex";
    static constexpr const char* Conditional = "Conditional";
  } // namespace Detail

  struct ParameterBase {
    virtual ~ParameterBase();
    virtual QString value() const = 0;
    virtual QString inputType() const = 0;
    virtual QString type() const = 0;
    virtual QString description() const = 0;
    virtual QString payload() const = 0;
    virtual bool isChooseable() const = 0;
    virtual bool update(const QString& str) = 0;
  };

  template <class T>
  class ParameterType : public ParameterBase {
    static_assert(std::is_enum_v<T> || std::is_arithmetic_v<T> ||
                      std::is_same_v<T, QString>,
                  "unsuported type.");

   protected:
    T& ref;
    QString about;

    static std::optional<T> eval(const QString& str) {
      if constexpr (std::is_enum_v<T>) {
        return static_cast<std::optional<T>>(MagicEnum::cast<T>(str));
      } else if constexpr (std::is_same_v<T, bool>) {
        if (str == "true" || str == "false") {
          return std::make_optional<T>(str == "true");
        } else {
          return std::nullopt;
        }
      } else if constexpr (std::is_arithmetic_v<T>) {
        T value;
        QString buffer = str;
        QTextStream stream(&buffer);
        stream >> value;
        if (stream.status() == QTextStream::Ok) {
          return std::make_optional<T>(std::move(value));
        } else {
          return std::nullopt;
        }
      } else if constexpr (std::is_same_v<T, QString>) {
        return std::make_optional<T>(str);
      }
    }

   public:
    ParameterType(T& t_ref, const QString& t_about = "") :
        ref(t_ref),
        about(t_about) {
      if constexpr (std::is_enum_v<T>) {
        if (!MagicEnum::contains(ref)) {
          throw std::runtime_error("enum value out of range.");
        }
      }
    }

    ~ParameterType() override {
    }

    QString value() const override {
      if constexpr (std::is_enum_v<T>) {
        return Utils::quoted(MagicEnum::name(ref));
      } else if constexpr (std::is_same_v<T, bool>) {
        return ref ? "true" : "false";
      }
      if constexpr (std::is_same_v<T, QString>) {
        return Utils::quoted(ref);
      } else if constexpr (std::is_floating_point_v<T>) {
        return QString::number(ref, 'f', 10);
      } else {
        return QString::number(ref);
      }
    }

    QString inputType() const override = 0;

    QString type() const override {
      return Utils::nameOfType<T>();
    }

    QString description() const override final {
      return about;
    }

    QString payload() const override = 0;
    bool isChooseable() const override = 0;

    bool update(const QString& str) override = 0;
  };

  template <class T>
  class Text : public ParameterType<T> {
    using ParameterType<T>::value;
    using ParameterType<T>::eval;
    using ParameterType<T>::ref;
    QRegularExpression regex;

   public:
    Text(T& t_ref,
         const QRegularExpression& t_regex = QRegularExpression("(.*)"),
         const QString& t_about = "") :
        ParameterType<T>(t_ref, t_about),
        regex(t_regex) {
      if (!regex.match(Utils::removeQuotes(static_cast<QString>(value())))
               .hasMatch()) {
        throw std::runtime_error("Text regex doesn't match.");
      }
    }

    QString inputType() const override final {
      return InputType::Text;
    }

    QString payload() const override final {
      return Utils::quoted(Detail::Regex) + ": " +
             Utils::quoted(regex.pattern());
    }

    bool isChooseable() const override final {
      return false;
    }

    bool update(const QString& str) override final {
      if (auto op = eval(str)) {
        if (regex.match(str).hasMatch()) {
          ref = *op;
          return true;
        }
      }
      return false;
    }
  };

  template <class T>
  class SpinBox : public ParameterType<T> {
    using ParameterType<T>::eval;
    using ParameterType<T>::ref;
    static_assert(std::is_integral_v<T>, "unsupported type.");
    T minValue;
    T maxValue;

   public:
    template <class U>
    SpinBox(T& t_ref, U t_minValue, U t_maxValue, const QString& t_about = "") :
        ParameterType<T>(t_ref, t_about) {
      if (!(t_minValue <= t_ref && t_ref <= t_maxValue)) {
        throw std::runtime_error("SpinBox ref value out of range.");
      }
      minValue = static_cast<T>(t_minValue);
      maxValue = static_cast<T>(t_maxValue);
    }

    QString inputType() const override final {
      return InputType::SpinBox;
    }

    QString payload() const override final {
      return Utils::quoted(Detail::MinValue) + ": " +
             QString::number(minValue) + ", " +
             Utils::quoted(Detail::MaxValue) + ": " + QString::number(maxValue);
    }

    bool isChooseable() const override final {
      return false;
    }

    bool update(const QString& str) override final {
      if (auto op = eval(str)) {
        if (minValue <= *op && *op <= maxValue) {
          ref = *op;
          return true;
        }
      }
      return false;
    }
  };

  template <class T>
  class DoubleSpinBox : public ParameterType<T> {
    using ParameterType<T>::eval;
    using ParameterType<T>::ref;
    static_assert(std::is_floating_point_v<T>, "unsupported type.");
    T minValue;
    T maxValue;
    int precision;

   public:
    template <class U>
    DoubleSpinBox(T& t_ref,
                  U t_minValue,
                  U t_maxValue,
                  int t_precision = 2,
                  const QString& t_about = "") :
        ParameterType<T>(t_ref, t_about) {
      if (!(t_minValue <= t_ref && t_ref <= t_maxValue)) {
        throw std::runtime_error("SpinBox ref value out of range.");
      }
      minValue = static_cast<T>(t_minValue);
      maxValue = static_cast<T>(t_maxValue);
      precision = t_precision;
    }

    QString value() const override final {
      return QString::number(ref, 'f', precision);
    }

    QString inputType() const override final {
      return InputType::DoubleSpinBox;
    }

    QString payload() const override final {
      return Utils::quoted(Detail::MinValue) + ": " +
             QString::number(minValue, 'f', precision) + ", " +
             Utils::quoted(Detail::MaxValue) + ": " +
             QString::number(maxValue, 'f', precision) + ", " +
             Utils::quoted(Detail::Precision) + ": " +
             QString::number(precision);
    }

    bool isChooseable() const override final {
      return false;
    }

    bool update(const QString& str) override final {
      if (auto op = eval(str)) {
        if (minValue <= *op && *op <= maxValue) {
          ref = *op;
          return true;
        }
      }
      return false;
    }
  };

  template <class T>
  class Slider : public ParameterType<T> {
    using ParameterType<T>::eval;
    using ParameterType<T>::ref;
    static_assert(std::is_integral_v<T>, "unsupported type.");
    T minValue;
    T maxValue;

   public:
    template <class U>
    Slider(T& t_ref, U t_minValue, U t_maxValue, const QString& t_about = "") :
        ParameterType<T>(t_ref, t_about) {
      if (!(t_minValue <= t_ref && t_ref <= t_maxValue)) {
        throw std::runtime_error("Slider ref value out of range.");
      }
      minValue = static_cast<T>(t_minValue);
      maxValue = static_cast<T>(t_maxValue);
    }

    QString inputType() const override final {
      return InputType::Slider;
    }

    QString payload() const override final {
      return Utils::quoted(Detail::MinValue) + ": " +
             QString::number(minValue) + ", " +
             Utils::quoted(Detail::MaxValue) + ": " + QString::number(maxValue);
    }

    bool isChooseable() const override final {
      return false;
    }

    bool update(const QString& str) override final {
      if (auto op = eval(str)) {
        if (minValue <= *op && *op <= maxValue) {
          ref = *op;
          return true;
        }
      }
      return false;
    }
  };

  class CheckBox : public ParameterType<bool> {
    using ParameterType<bool>::eval;
    using ParameterType<bool>::ref;

   public:
    CheckBox(bool& t_ref, const QString& t_about = "") :
        ParameterType<bool>(t_ref, t_about) {
    }

    QString inputType() const override final {
      return InputType::CheckBox;
    }

    QString payload() const override final {
      return "";
    }

    bool isChooseable() const override final {
      return true;
    }

    bool update(const QString& str) override final {
      if (auto op = eval(str)) {
        ref = *op;
        return true;
      }
      return false;
    }
  };

  template <class T>
  class ComboBox : public ParameterType<T> {
    using ParameterType<T>::eval;
    using ParameterType<T>::ref;
    std::set<T> set;

   public:
    ComboBox(T& t_ref, const QVector<T>& t_set, const QString& t_about = "") :
        ParameterType<T>(t_ref, t_about),
        set(t_set.begin(), t_set.end()) {
      if (!((set.size() > 1) && set.find(t_ref) != set.end())) {
        throw std::runtime_error(
            "the size of set must be greater than 1, and must contain ref.");
      }
    }

    QString type() const override final {
      return Utils::nameOfType<T>();
    }

    QString inputType() const override final {
      return InputType::ComboBox;
    }

    QString payload() const override final {
      QString options;
      QTextStream stream(&options);
      stream << Qt::fixed;

      for (auto it = set.begin(); it != set.end(); ++it) {
        const T& value = *it;
        if constexpr (std::is_same_v<T, QString>) {
          stream << Utils::quoted(value);
        } else if constexpr (std::is_enum_v<T>) {
          stream << Utils::quoted(MagicEnum::name(value));
        } else {
          stream << value;
        }
        if (std::next(it) != set.end()) {
          stream << ", ";
        }
      }
      options = "[" + options + "]";
      return Utils::quoted(Detail::Options) + ": " + options;
    }

    bool isChooseable() const override final {
      return true;
    }

    bool update(const QString& str) override final {
      if (auto op = eval(str)) {
        if (set.find(*op) != set.end()) {
          ref = *op;
          return true;
        }
      }
      return false;
    }
  };

  template <class T>
  class MappedComboBox : public ParameterType<T> {
    using ParameterType<T>::eval;
    using ParameterType<T>::ref;
    boost::bimap<T, QString> bimap;

   public:
    MappedComboBox(T& t_ref,
                   const QMap<T, QString>& t_map,
                   const QString& t_about = "") :
        ParameterType<T>(t_ref, t_about),
        bimap([](const QMap<T, QString>& map) {
          boost::bimap<T, QString> ret;
          for (auto it = map.begin(); it != map.end(); ++it) {
            ret.insert({it.key(), it.value()});
          }
          return ret;
        }(t_map)) {
      bool contains = bimap.left.find(t_ref) != bimap.left.end();
      if (!((bimap.size() > 1) &&
            (static_cast<int>(bimap.size()) == t_map.size()) && contains)) {
        throw std::runtime_error(
            "the size of map must be greater than 1, and must contain ref.");
      }
    }

    QString value() const override {
      auto it = bimap.left.find(ParameterType<T>::ref);
      if (it == bimap.left.end()) {
        throw std::runtime_error("the value was not found.");
      } else {
        return Utils::quoted(it->second);
      }
    }

    QString inputType() const override final {
      return InputType::ComboBox;
    }

    QString type() const override final {
      return "mapped(" + Utils::nameOfType<T>() + ")";
    }

    QString payload() const override final {
      QString options;
      QTextStream stream(&options);
      stream << Qt::fixed;

      for (auto it = bimap.right.begin(); it != bimap.right.end(); ++it) {
        stream << Utils::quoted(it->first);

        if (std::next(it) != bimap.right.end()) {
          stream << ", ";
        }
      }
      options = "[" + options + "]";
      return Utils::quoted(Detail::Options) + ": " + options;
    }

    bool isChooseable() const override final {
      return true;
    }

    bool update(const QString& str) override final {
      if (auto it = bimap.right.find(str); it != bimap.right.end()) {
        ref = bimap.right.find(str)->get_left();
        return true;
      }
      return false;
    }
  };
} // namespace Parameters

#endif // PARAMETERTYPE_H
