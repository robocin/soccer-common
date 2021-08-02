#ifndef SOCCER_COMMON_PARAMETERTYPE_H
#define SOCCER_COMMON_PARAMETERTYPE_H

#include <set>
#include <QString>
#include <QFileDialog>
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
    static constexpr const char* PushButton = "PushButton";
    static constexpr const char* File = "File";
    static constexpr const char* Directory = "Directory";
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
    static constexpr const char* Parent = "Parent";
    static constexpr const char* Filter = "Filter";
    static constexpr const char* DefaultDirectory = "DefaultDirectory";
  } // namespace Detail

  struct ParameterBase {
    virtual ~ParameterBase() = default;
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
    using value_type = T;

    // disable_empty_constructor:
    Arg() = delete;

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
    static_assert(std::is_enum_v<T> ||
                      (std::is_arithmetic_v<T> && !(detail::is_any_of_v<T, char, long double>) ) ||
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
        static const QStringList options = {"0", "1", "false", "true"};
        if (options.contains(str, Qt::CaseInsensitive)) {
          return std::make_optional<T>(str == "1" || str.toLower() == "true");
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
        return QString::number(ref.value(), 'f', 15);
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
   public:
    using value_type = typename Arg<T>::value_type;

   private:
    using ParameterType<T>::setValue;
    using ParameterType<T>::eval;
    using ParameterType<T>::ref;
    QRegularExpression regex;

   public:
    using ParameterType<T>::value;

    explicit Text(Arg<T>& t_ref,
                  QRegularExpression t_regex = Regex::AnyMatch,
                  const QString& t_about = "") :
        ParameterType<T>(t_ref, t_about),
        regex(std::move(t_regex)) {
      if (!regex.match(Utils::removeQuotes(static_cast<QString>(value()))).hasMatch()) {
        throw std::runtime_error("Text regex doesn't match.");
      }
    }

    QString inputType() const override final {
      return InputType::Text;
    }

    QString payload() const override final {
      return Utils::quoted(Detail::Regex) + ": " + Utils::quoted(regex.pattern());
    }

    bool isChooseable() const override final {
      return false;
    }

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

  template <class T, std::enable_if_t<std::is_base_of_v<T, QString>, bool> = true>
  class File : public ParameterType<T> {
   public:
    using value_type = typename Arg<T>::value_type;

   private:
    using ParameterType<T>::setValue;
    using ParameterType<T>::eval;
    using ParameterType<T>::ref;
    QString filter;
    QString defaultDirectory;

   public:
    using ParameterType<T>::value;

    explicit File(Arg<T>& t_ref,
                  QString t_filter = "",
                  QString t_defaultDirectory = "",
                  const QString& t_about = "") :
        ParameterType<T>(t_ref, t_about),
        filter(std::move(t_filter)),
        defaultDirectory(std::move(t_defaultDirectory)) {
      if (!Utils::removeQuotes(static_cast<QString>(value())).isEmpty()) {
        if (!QFile::exists(Utils::removeQuotes(static_cast<QString>(value())))) {
          throw std::runtime_error("t_ref must be empty or a valid file.");
        }
      }
    }

    QString inputType() const override final {
      return InputType::File;
    }

    QString payload() const override final {
      return Utils::quoted(Detail::Filter) + ": " + Utils::quoted(filter) + ", " +
             Utils::quoted(Detail::DefaultDirectory) + ": " + Utils::quoted(defaultDirectory);
    }

    bool isChooseable() const override final {
      return false;
    }

    bool update(const QString& str) override final {
      if (auto op = eval(str)) {
        setValue(*op);
        return true;
      }
      return false;
    }
  };

  template <class T, std::enable_if_t<std::is_base_of_v<T, QString>, bool> = true>
  class Directory : public ParameterType<T> {
   public:
    using value_type = typename Arg<T>::value_type;

   private:
    using ParameterType<T>::setValue;
    using ParameterType<T>::eval;
    using ParameterType<T>::ref;
    QString options;
    QString defaultDirectory;

   public:
    using ParameterType<T>::value;

    explicit Directory(Arg<T>& t_ref,
                       const QFileDialog::Option& t_options = QFileDialog::Option::ShowDirsOnly,
                       QString t_defaultDirectory = "",
                       const QString& t_about = "") :
        ParameterType<T>(t_ref, t_about),
        options(MagicEnum::name(t_options)),
        defaultDirectory(std::move(t_defaultDirectory)) {
      if (!Utils::removeQuotes(static_cast<QString>(value())).isEmpty()) {
        if (!QDir(Utils::removeQuotes(static_cast<QString>(value()))).exists()) {
          throw std::runtime_error("t_ref must be empty or a valid directory.");
        }
      }
    }

    QString inputType() const override final {
      return InputType::Directory;
    }

    QString payload() const override final {
      return Utils::quoted(Detail::Options) + ": " + Utils::quoted(options) + ", " +
             Utils::quoted(Detail::DefaultDirectory) + ": " + Utils::quoted(defaultDirectory);
    }

    bool isChooseable() const override final {
      return false;
    }

    bool update(const QString& str) override final {
      if (auto op = eval(str)) {
        setValue(*op);
        return true;
      }
      return false;
    }
  };

  template <class T>
  class SpinBox : public ParameterType<T> {
   public:
    using value_type = typename Arg<T>::value_type;

   private:
    using ParameterType<T>::setValue;
    using ParameterType<T>::eval;
    using ParameterType<T>::ref;

    static_assert(std::is_integral_v<T>, "unsupported type.");

    value_type minValue;
    value_type maxValue;

   public:
    SpinBox(Arg<T>& t_ref,
            value_type t_minValue,
            value_type t_maxValue,
            const QString& t_about = "") :
        ParameterType<T>(t_ref, t_about) {
      if (t_minValue >= t_maxValue) {
        throw std::runtime_error("minValue is greater or equal than maxValue.");
      }
      if (!(t_minValue <= t_ref && t_ref <= t_maxValue)) {
        throw std::runtime_error("SpinBox ref value out of range.");
      }
      minValue = t_minValue;
      maxValue = t_maxValue;
    }

    QString inputType() const override final {
      return InputType::SpinBox;
    }

    QString payload() const override final {
      return Utils::quoted(Detail::MinValue) + ": " + QString::number(minValue) + ", " +
             Utils::quoted(Detail::MaxValue) + ": " + QString::number(maxValue);
    }

    bool isChooseable() const override final {
      return false;
    }

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
   public:
    using value_type = typename Arg<T>::value_type;

   protected:
    using ParameterType<T>::setValue;
    using ParameterType<T>::eval;
    using ParameterType<T>::ref;

    static_assert(std::is_floating_point_v<T>, "unsupported type.");

    value_type minValue{};
    value_type maxValue{};
    int precision{};

    explicit DoubleSpinBox(Arg<T>& t_ref, const QString& t_about = "") :
        ParameterType<T>(t_ref, t_about) {
    }

   public:
    DoubleSpinBox(Arg<T>& t_ref,
                  value_type t_minValue,
                  value_type t_maxValue,
                  int t_precision = 2,
                  const QString& t_about = "") :
        ParameterType<T>(t_ref, t_about) {
      if (t_minValue >= t_maxValue) {
        throw std::runtime_error("minValue is greater or equal than maxValue.");
      }
      if (!(t_minValue <= t_ref && t_ref <= t_maxValue)) {
        throw std::runtime_error("SpinBox ref value out of range.");
      }
      if (!(0 <= t_precision && t_precision <= 15)) {
        throw std::runtime_error("SpinBox precision value out of range.");
      }
      minValue = t_minValue;
      maxValue = t_maxValue;
      precision = t_precision;
    }

    QString value() const override {
      return QString::number(ref.value(), 'f', precision);
    }

    QString inputType() const override final {
      return InputType::DoubleSpinBox;
    }

    QString payload() const override final {
      return Utils::quoted(Detail::MinValue) + ": " + QString::number(minValue, 'f', precision) +
             ", " + Utils::quoted(Detail::MaxValue) + ": " +
             QString::number(maxValue, 'f', precision) + ", " + Utils::quoted(Detail::Precision) +
             ": " + QString::number(precision);
    }

    bool isChooseable() const override final {
      return false;
    }

    bool update(const QString& str) override {
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
  class MappedAngleInRadiansToDegrees : public DoubleSpinBox<T> {
   public:
    using value_type = typename DoubleSpinBox<T>::value_type;

   private:
    using DoubleSpinBox<T>::setValue;
    using DoubleSpinBox<T>::eval;
    using DoubleSpinBox<T>::ref;
    using DoubleSpinBox<T>::minValue;
    using DoubleSpinBox<T>::maxValue;
    using DoubleSpinBox<T>::precision;

    static constexpr double PI = qDegreesToRadians(180.0);

    static QString message(QString about) {
      if (!about.isEmpty()) {
        about += " ";
      }
      about += "(input in degrees mapped to radians)";
      return about;
    }

   public:
    explicit MappedAngleInRadiansToDegrees(Arg<T>& t_ref,
                                           value_type t_minValue = -PI,
                                           value_type t_maxValue = +PI,
                                           int t_precision = 2,
                                           const QString& t_about = "") :
        DoubleSpinBox<T>(t_ref, message(t_about)) {
      if (t_minValue >= t_maxValue) {
        throw std::runtime_error("minValue is greater or equal than maxValue.");
      }
      if (!(t_minValue <= t_ref && t_ref <= t_maxValue)) {
        throw std::runtime_error("SpinBox ref value out of range.");
      }
      if (!(0 <= t_precision && t_precision <= 15)) {
        throw std::runtime_error("SpinBox precision value out of range.");
      }
      minValue = qRadiansToDegrees(t_minValue);
      maxValue = qRadiansToDegrees(t_maxValue);
      precision = t_precision;
    }

    QString value() const override final {
      return QString::number(qRadiansToDegrees(ref.value()), 'f', precision);
    }

    bool update(const QString& str) override final {
      if (auto op = eval(str)) {
        if (minValue <= *op && *op <= maxValue) {
          setValue(qDegreesToRadians(*op));
          return true;
        }
      }
      return false;
    }
  };

  template <class T>
  class Slider : public ParameterType<T> {
   public:
    using value_type = typename Arg<T>::value_type;

   private:
    using ParameterType<T>::setValue;
    using ParameterType<T>::eval;
    using ParameterType<T>::ref;

    static_assert(std::is_integral_v<T>, "unsupported type.");

    value_type minValue;
    value_type maxValue;

   public:
    Slider(Arg<T>& t_ref,
           value_type t_minValue,
           value_type t_maxValue,
           const QString& t_about = "") :
        ParameterType<T>(t_ref, t_about) {
      if (t_minValue >= t_maxValue) {
        throw std::runtime_error("minValue is greater or equal than maxValue.");
      }
      if (!(t_minValue <= t_ref && t_ref <= t_maxValue)) {
        throw std::runtime_error("Slider ref value out of range.");
      }
      minValue = t_minValue;
      maxValue = t_maxValue;
    }

    QString inputType() const override final {
      return InputType::Slider;
    }

    QString payload() const override final {
      return Utils::quoted(Detail::MinValue) + ": " + QString::number(minValue) + ", " +
             Utils::quoted(Detail::MaxValue) + ": " + QString::number(maxValue);
    }

    bool isChooseable() const override final {
      return false;
    }

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
   public:
    using value_type = typename Arg<bool>::value_type;

   private:
    using ParameterType<bool>::setValue;
    using ParameterType<bool>::eval;
    using ParameterType<bool>::ref;

   public:
    explicit CheckBox(Arg<bool>& t_ref, const QString& t_about = "") :
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
        setValue(*op);
        return true;
      }
      return false;
    }
  };

  template <class T>
  class ComboBox : public ParameterType<T> {
   public:
    using value_type = typename Arg<T>::value_type;

   private:
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

    bool isChooseable() const override final {
      return true;
    }

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
   public:
    using value_type = typename Arg<T>::value_type;

   private:
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

    QString value() const override {
      auto it = bimap.left.find(ParameterType<T>::ref.value());
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
        setValue(bimap.right.find(str)->get_left());
        return true;
      }
      return false;
    }
  };

  class PushButton : public ParameterBase {
    QString m_type;
    QString m_about;
    qulonglong m_parent;
    std::function<void()> m_function;

   public:
    template <class FunctionPointer>
    explicit PushButton(QObject* t_parent, FunctionPointer&& t_f, QString t_about = "") :
        m_type(Utils::nameOfType<FunctionPointer>()),
        m_parent(reinterpret_cast<qulonglong>(t_parent)),
        m_function(std::forward<FunctionPointer>(t_f)),
        m_about(std::move(t_about)) {
      if (!t_parent) {
        throw std::runtime_error("t_parent must be a valid pointer.");
      }
    }

    QString value() const override final {
      return Utils::quoted(QString::number(reinterpret_cast<qulonglong>(&m_function)));
    }

    QString inputType() const override final {
      return InputType::PushButton;
    }

    QString type() const override final {
      return m_type;
    }

    QString description() const override final {
      return m_about;
    }

    QString payload() const override final {
      return Utils::quoted(Detail::Parent) + ": " + Utils::quoted(QString::number(m_parent));
    }

    bool isChooseable() const override final {
      return false;
    }

    bool update(const QString&) override final {
      return false;
    }
  };
} // namespace Parameters

#endif // SOCCER_COMMON_PARAMETERTYPE_H
