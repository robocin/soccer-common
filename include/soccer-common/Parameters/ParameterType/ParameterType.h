#ifndef SOCCER_COMMON_PARAMETERTYPE_H
#define SOCCER_COMMON_PARAMETERTYPE_H

#include <set>
#include <QString>
#include <QTextStream>
#include <boost/bimap.hpp>
#include <QRegularExpression>
#include <utility>
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
  class ParameterType;

  template <class T>
  class Arg {
    friend class ParameterType<T>;

    T m_value;
    mutable bool m_updated{};

    template <class U>
    void set(U&& value) {
      m_updated = true;
      m_value = std::forward<U>(value);
    }

   public:
    using type = T;

    template <class... Us>
    Arg(Us&&... us) : m_value(std::forward<Us>(us)...), m_updated(false) {
    }

    // disable_copy:
    Arg(const Arg&) = delete;
    Arg& operator=(const Arg&) = delete;

    const T& value() const {
      return m_value;
    }

    operator const T&() const { // NOLINT(google-explicit-constructor)
      return m_value;
    }

    bool updated() const {
      return m_updated ? (m_updated = false, true) : m_updated;
    }
  };

  template <class T>
  class ParameterType : public ParameterBase {
    template <class U, class... Us>
    static constexpr bool is_any_of_v = std::disjunction_v<std::is_same<U, Us>...>;

    static_assert(std::is_enum_v<T> ||
                      (std::is_arithmetic_v<T> && !(is_any_of_v<T, char, long double>) ) ||
                      std::is_base_of_v<T, QString>,
                  "unsupported type.");

   protected:
    Arg<T>& ref;
    QString about;

    template <class U>
    void setValue(U&& value) {
      ref.set(std::forward<U>(value));
    }

   public:
    static std::optional<T> eval(const QString& str) {
      if constexpr (std::is_enum_v<T>) {
        return static_cast<std::optional<T>>(MagicEnum::cast<T>(str));
      } else if constexpr (std::is_same_v<T, bool>) {
        if (auto var = QVariant(str); var.canConvert<bool>()) {
          return std::make_optional<T>(var.toBool());
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
      } else if constexpr (std::is_base_of_v<QString, T>) {
        return std::make_optional<T>(str);
      }
    }

    explicit ParameterType(Arg<T>& t_ref, QString t_about = "") :
        ref(t_ref),
        about(std::move(t_about)) {
      if constexpr (std::is_enum_v<T>) {
        if (!MagicEnum::contains(ref.value())) {
          throw std::runtime_error("enum value out of range.");
        }
      }
    }

    ~ParameterType() override = default;

    QString value() const override {
      if constexpr (std::is_enum_v<T>) {
        return Utils::quoted(MagicEnum::name(ref.value()));
      } else if constexpr (std::is_same_v<T, bool>) {
        return ref.value() ? "true" : "false";
      } else if constexpr (std::is_floating_point_v<T>) {
        return QString::number(ref.value(), 'f', 10);
      } else if constexpr (std::is_arithmetic_v<T>) {
        return QString::number(ref.value());
      } else if constexpr (std::is_base_of_v<QString, T>) {
        return Utils::quoted(ref.value());
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
    using ParameterType<T>::setValue;
    using ParameterType<T>::eval;
    using ParameterType<T>::ref;
    QRegularExpression regex;

   public:
    using ParameterType<T>::value;

    explicit Text(Arg<T>& t_ref,
                  const QRegularExpression& t_regex = Regex::AnyMatch,
                  const QString& t_about = "") :
        ParameterType<T>(t_ref, t_about),
        regex(t_regex) {
      if (!regex.match(Utils::removeQuotes(static_cast<QString>(value()))).hasMatch()) {
        throw std::runtime_error("Text regex doesn't match.");
      }
    }
    /*!
    * @return Returns the input type.
    */
    QString inputType() const override final {
      return InputType::Text;
    }

    QString payload() const override final {
      return Utils::quoted(Detail::Regex) + ": " + Utils::quoted(regex.pattern());
    }
    /*!
    * @return Returns if is Chooseable.
    */
    bool isChooseable() const override final {
      return false;
    }
    /*!
    * @tparam str Qstring type.
    * @return Return true if find the str and updated this, else return false.
    * 
    */
    bool update(const QString& str) override final {
      if (auto op = eval(str)) {
        if (regex.match(str).hasMatch()) {
          setValue(*op);
          return true;
        }
      }
      return false;
    }
  };

  template <class T>
  class SpinBox : public ParameterType<T> {
    using ParameterType<T>::setValue;
    using ParameterType<T>::eval;
    using ParameterType<T>::ref;
    static_assert(std::is_integral_v<T>, "unsupported type.");
    T minValue;
    T maxValue;

   public:
    template <class U>
    SpinBox(Arg<T>& t_ref, U t_minValue, U t_maxValue, const QString& t_about = "") :
        ParameterType<T>(t_ref, t_about) {
      if (t_minValue >= t_maxValue) {
        throw std::runtime_error("minValue is greater or equal than maxValue.");
      }
      if (!(t_minValue <= t_ref && t_ref <= t_maxValue)) {
        throw std::runtime_error("SpinBox ref value out of range.");
      }
      minValue = static_cast<T>(t_minValue);
      maxValue = static_cast<T>(t_maxValue);
    }
    /*!
    * @return Returns the input Type.
    * 
    */
    QString inputType() const override final {
      return InputType::SpinBox;
    }
    /*!
    * @return Returns the min value and the max value.
    * 
    */
    QString payload() const override final {
      return Utils::quoted(Detail::MinValue) + ": " + QString::number(minValue) + ", " +
             Utils::quoted(Detail::MaxValue) + ": " + QString::number(maxValue);
    }
    /*!
    * @return Returns if is Chooseable.
    * 
    */
    bool isChooseable() const override final {
      return false;
    }
    /*!
    * @tparam str Qstring type.
    * @return Return true if find the str and updated this, else return false.
    * 
    */
    bool update(const QString& str) override final {
      if (auto op = eval(str)) {
        if (minValue <= *op && *op <= maxValue) {
          setValue(*op);
          return true;
        }
      }
      return false;
    }
  };

  template <class T>
  class DoubleSpinBox : public ParameterType<T> {
    using ParameterType<T>::setValue;
    using ParameterType<T>::eval;
    using ParameterType<T>::ref;
    static_assert(std::is_floating_point_v<T>, "unsupported type.");
    T minValue;
    T maxValue;
    int precision;

   public:
    template <class U>
    DoubleSpinBox(Arg<T>& t_ref,
                  U t_minValue,
                  U t_maxValue,
                  int t_precision = 2,
                  const QString& t_about = "") :
        ParameterType<T>(t_ref, t_about) {
      if (t_minValue >= t_maxValue) {
        throw std::runtime_error("minValue is greater or equal than maxValue.");
      }
      if (!(t_minValue <= t_ref && t_ref <= t_maxValue)) {
        throw std::runtime_error("SpinBox ref value out of range.");
      }
      minValue = static_cast<T>(t_minValue);
      maxValue = static_cast<T>(t_maxValue);
      precision = t_precision;
    }
    /*!
    * @return Returns the value and the precision.
    * 
    */
    QString value() const override final {
      return QString::number(ref.value(), 'f', precision);
    }
    /*!
    * @return Returns the input type.
    * 
    */
    QString inputType() const override final {
      return InputType::DoubleSpinBox;
    }
    /*!
    * @return Returns the min value with the precision and the max value with the precision
    */
    QString payload() const override final {
      return Utils::quoted(Detail::MinValue) + ": " + QString::number(minValue, 'f', precision) +
             ", " + Utils::quoted(Detail::MaxValue) + ": " +
             QString::number(maxValue, 'f', precision) + ", " + Utils::quoted(Detail::Precision) +
             ": " + QString::number(precision);
    }
    /*!
    * @return Returns if is Chooseable.
    * 
    */
    bool isChooseable() const override final {
      return false;
    }
    /*!
    * @tparam str Qstring type.
    * @return Return true if find the str and updated this, else return false.
    * 
    */
    bool update(const QString& str) override final {
      if (auto op = eval(str)) {
        if (minValue <= *op && *op <= maxValue) {
          setValue(*op);
          return true;
        }
      }
      return false;
    }
  };

  template <class T>
  class Slider : public ParameterType<T> {
    using ParameterType<T>::setValue;
    using ParameterType<T>::eval;
    using ParameterType<T>::ref;
    static_assert(std::is_integral_v<T>, "unsupported type.");
    T minValue;
    T maxValue;

   public:
    template <class U>
    Slider(Arg<T>& t_ref, U t_minValue, U t_maxValue, const QString& t_about = "") :
        ParameterType<T>(t_ref, t_about) {
      if (t_minValue >= t_maxValue) {
        throw std::runtime_error("minValue is greater or equal than maxValue.");
      }
      if (!(t_minValue <= t_ref && t_ref <= t_maxValue)) {
        throw std::runtime_error("Slider ref value out of range.");
      }
      minValue = static_cast<T>(t_minValue);
      maxValue = static_cast<T>(t_maxValue);
    }
    /*!
    * @return Returns the input type.
    * 
    */
    QString inputType() const override final {
      return InputType::Slider;
    }
    /*!
    * @return Returns the min value and the max value.
    */
    QString payload() const override final {
      return Utils::quoted(Detail::MinValue) + ": " + QString::number(minValue) + ", " +
             Utils::quoted(Detail::MaxValue) + ": " + QString::number(maxValue);
    }
    /*!
    * @return Returns if is Chooseable.
    * 
    */
    bool isChooseable() const override final {
      return false;
    }
    /*!
    * @tparam str Qstring type.
    * @return Return true if find the str and updated this, else return false.
    * 
    */
    bool update(const QString& str) override final {
      if (auto op = eval(str)) {
        if (minValue <= *op && *op <= maxValue) {
          setValue(*op);
          return true;
        }
      }
      return false;
    }
  };

  class CheckBox : public ParameterType<bool> {
    using ParameterType<bool>::setValue;
    using ParameterType<bool>::eval;
    using ParameterType<bool>::ref;

   public:
    explicit CheckBox(Arg<bool>& t_ref, const QString& t_about = "") :
        ParameterType<bool>(t_ref, t_about) {
    }
    /*!
    * @return Returns the input type.
    * 
    */
    QString inputType() const override final {
      return InputType::CheckBox;
    }

    QString payload() const override final {
      return "";
    }
    /*!
    * @return Returns if is Chooseable.
    * 
    */
    bool isChooseable() const override final {
      return true;
    }
  /*!
    * @tparam str Qstring type.
    * @return Return true if find the str and updated this, else return false.
    * 
    */
    bool update(const QString& str) override final {
      if (auto op = eval(str)) {
        setValue(*op);
        return true;
      }
      return false;
    }
  };

  template <class T>
  class ComboBox : public ParameterType<T> {
    using ParameterType<T>::setValue;
    using ParameterType<T>::eval;
    using ParameterType<T>::ref;
    std::set<T> set;

   public:
    ComboBox(Arg<T>& t_ref, const QVector<T>& t_set, const QString& t_about = "") :
        ParameterType<T>(t_ref, t_about),
        set(t_set.begin(), t_set.end()) {
      if (!((set.size() > 1) && set.find(t_ref) != set.end())) {
        throw std::runtime_error("the size of set must be greater than 1, and must contain ref.");
      }
    }
    /*!
    * @return Returns the name of type.
    * 
    */
    QString type() const override final {
      return Utils::nameOfType<T>();
    }
    /*!
    * @return Returns the input type.
    * 
    */
    QString inputType() const override final {
      return InputType::ComboBox;
    }

    QString payload() const override final {
      QString options;
      QTextStream stream(&options);
      stream << Qt::fixed;

      for (auto it = set.begin(); it != set.end(); ++it) {
        const T& value = *it;
        if constexpr (std::is_base_of_v<QString, T>) {
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
    /*!
    * @return Returns if is Chooseable.
    * 
    */
    bool isChooseable() const override final {
      return true;
    }
    /*!
    * @tparam str Qstring type.
    * @return Return true if find the str and updated this, else return false.
    * 
    */
    bool update(const QString& str) override final {
      if (auto op = eval(str)) {
        if (set.find(*op) != set.end()) {
          setValue(*op);
          return true;
        }
      }
      return false;
    }
  };

  template <class T>
  class MappedComboBox : public ParameterType<T> {
    using ParameterType<T>::setValue;
    using ParameterType<T>::eval;
    using ParameterType<T>::ref;
    boost::bimap<T, QString> bimap;

   public:
    MappedComboBox(Arg<T>& t_ref, const QMap<T, QString>& t_map, const QString& t_about = "") :
        ParameterType<T>(t_ref, t_about),
        bimap([](const QMap<T, QString>& map) {
          boost::bimap<T, QString> ret;
          for (auto it = map.begin(); it != map.end(); ++it) {
            ret.insert({it.key(), it.value()});
          }
          return ret;
        }(t_map)) {
      bool contains = bimap.left.find(t_ref) != bimap.left.end();
      if (!((bimap.size() > 1) && (static_cast<int>(bimap.size()) == t_map.size()) && contains)) {
        throw std::runtime_error("the size of map must be greater than 1, and must contain ref.");
      }
    }
  /*!
   * @return Return the value if find it, else has a Runtime Error.
   * 
   */
    QString value() const override {
      auto it = bimap.left.find(ParameterType<T>::ref.value());
      if (it == bimap.left.end()) {
        throw std::runtime_error("the value was not found.");
      } else {
        return Utils::quoted(it->second);
      }
    }
    /*!
    * @return Returns the input type.
    * 
    */
    QString inputType() const override final {
      return InputType::ComboBox;
    }
   /*!
    * @return Returns "mapped" with the variable type.
    * 
    */
    QString type() const override final {
      return "mapped(" + Utils::nameOfType<T>() + ")";
    }
   /*!
    * @param options 
    */
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
    /*!
    * @return Returns if is Chooseable.
    * 
    */
    bool isChooseable() const override final {
      return true;
    }
   /*!
    * @tparam str Qstring type.
    * @return Return true if find the str and updated this, else return false.
    * 
    */
    bool update(const QString& str) override final {
      if (auto it = bimap.right.find(str); it != bimap.right.end()) {
        setValue(bimap.right.find(str)->get_left());
        return true;
      }
      return false;
    }
  };
} // namespace Parameters

#endif // SOCCER_COMMON_PARAMETERTYPE_H
