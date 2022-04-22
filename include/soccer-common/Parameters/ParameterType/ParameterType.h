#ifndef SOCCER_COMMON_PARAMETERTYPE_H
#define SOCCER_COMMON_PARAMETERTYPE_H

#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nodiscard"

#include <set>
#include <QString>
#include <QFileDialog>
#include <QTextStream>
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
    virtual bool isChoosable() const = 0;
    virtual bool update(const QString& str) = 0;

    virtual void setUpdated(bool updated) = 0;
  };

  template <class T>
  class ParameterType;

  template <class T>
  class Arg {
    static_assert(std::is_enum_v<T> ||
                      (std::is_arithmetic_v<T> && !(detail::is_any_of_v<T, char, long double>) ) ||
                      std::is_base_of_v<T, QString>,
                  "unsupported type.");

    friend class ParameterType<T>;

    T m_value;
    mutable bool m_updated;

    template <class U>
    void set(U&& value) {
      m_value = std::forward<U>(value);
    }

    void setUpdated(bool updated) {
      m_updated = updated;
    }

   public:
    using value_type = T;

    // disable_empty_constructor:
    Arg() = delete;

    template <class U>
    Arg(U value) : m_value(value), m_updated(false) { // NOLINT(google-explicit-constructor)
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
      return m_updated;
    }
  };

  template <class T>
  class Arg<std::atomic<T>> {
    friend class ParameterType<std::atomic<T>>;

    std::atomic<T> m_value;

    template <class U>
    void set(U&& value) {
      m_value.store(std::forward<U>(value));
    }

    void setUpdated(bool) {
    }

   public:
    using value_type = T;

    // disable_empty_constructor:
    Arg() = delete;

    template <class U>
    Arg(U value) : m_value(value) { // NOLINT(google-explicit-constructor)
    }

    // disable_copy:
    Arg(const Arg&) = delete;
    Arg& operator=(const Arg&) = delete;

    T value() const {
      return m_value.load();
    }

    operator T() const { // NOLINT(google-explicit-constructor)
      return m_value.load();
    }
  };

  template <class T>
  using Atomic = Arg<std::atomic<T>>;

  template <class T>
  class ParameterType : public ParameterBase {
   protected:
    Arg<T>& ref;
    QString about;

    template <class U>
    void setValue(U&& value) {
      ref.set(std::forward<U>(value));
    }

   public:
    using value_type = typename Arg<T>::value_type;

    static std::optional<value_type> eval(const QString& str) {
      if constexpr (std::is_enum_v<value_type>) {
        return static_cast<std::optional<value_type>>(MagicEnum::cast<value_type>(str));
      } else if constexpr (std::is_same_v<value_type, bool>) {
        static const QStringList options = {"0", "1", "false", "true"};
        if (options.contains(str, Qt::CaseInsensitive)) {
          return std::make_optional<value_type>(str == "1" || str.toLower() == "true");
        } else {
          return std::nullopt;
        }
      } else if constexpr (std::is_arithmetic_v<value_type>) {
        value_type value;
        QString buffer = str;
        QTextStream stream(&buffer);
        stream >> value;
        if (stream.status() == QTextStream::Ok) {
          return std::make_optional<value_type>(std::move(value));
        } else {
          return std::nullopt;
        }
      } else if constexpr (std::is_base_of_v<QString, value_type>) {
        return std::make_optional<value_type>(str);
      }
    }

    explicit ParameterType(Arg<T>& t_ref, QString t_about = "") :
        ref(t_ref),
        about(std::move(t_about)) {
      if constexpr (std::is_enum_v<value_type>) {
        if (!MagicEnum::contains(ref.value())) {
          throw std::runtime_error("enum value out of range.");
        }
      }
    }

    ~ParameterType() override = default;

    QString value() const override {
      if constexpr (std::is_enum_v<value_type>) {
        return Utils::quoted(MagicEnum::name(ref.value()));
      } else if constexpr (std::is_same_v<value_type, bool>) {
        return ref.value() ? "true" : "false";
      } else if constexpr (std::is_floating_point_v<value_type>) {
        return QString::number(ref.value(), 'f', 15);
      } else if constexpr (std::is_arithmetic_v<value_type>) {
        return QString::number(ref.value());
      } else if constexpr (std::is_base_of_v<QString, value_type>) {
        return Utils::quoted(ref.value());
      }
    }

    QString inputType() const override = 0;

    QString type() const override {
      return Utils::nameOfType<value_type>();
    }

    QString description() const final {
      return about;
    }

    QString payload() const override = 0;
    bool isChoosable() const override = 0;

    bool update(const QString& str) override = 0;

    void setUpdated(bool updated) final {
      ref.setUpdated(updated);
    }
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

    QString inputType() const final {
      return InputType::Text;
    }

    QString payload() const final {
      return Utils::quoted(Detail::Regex) + ": " + Utils::quoted(regex.pattern());
    }

    bool isChoosable() const final {
      return false;
    }

    bool update(const QString& str) final {
      if (auto op = eval(str)) {
        if (regex.match(str).hasMatch()) {
          setValue(*op);
          return true;
        }
      }
      return false;
    }
  };

  template <class T,
            std::enable_if_t<std::is_base_of_v<typename Arg<T>::value_type, QString>, bool> = true>
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

    QString inputType() const final {
      return InputType::File;
    }

    QString payload() const final {
      return Utils::quoted(Detail::Filter) + ": " + Utils::quoted(filter) + ", " +
             Utils::quoted(Detail::DefaultDirectory) + ": " + Utils::quoted(defaultDirectory);
    }

    bool isChoosable() const final {
      return false;
    }

    bool update(const QString& str) final {
      if (auto op = eval(str)) {
        if (op.value().isEmpty() || QFile::exists(op.value())) {
          setValue(*op);
          return true;
        }
      }
      return false;
    }
  };

  template <class T,
            std::enable_if_t<std::is_base_of_v<typename Arg<T>::value_type, QString>, bool> = true>
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

    QString inputType() const final {
      return InputType::Directory;
    }

    QString payload() const final {
      return Utils::quoted(Detail::Options) + ": " + Utils::quoted(options) + ", " +
             Utils::quoted(Detail::DefaultDirectory) + ": " + Utils::quoted(defaultDirectory);
    }

    bool isChoosable() const final {
      return false;
    }

    bool update(const QString& str) final {
      if (auto op = eval(str)) {
        if (op.value().isEmpty() || QDir(op.value()).exists()) {
          setValue(*op);
          return true;
        }
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

    static_assert(std::is_integral_v<value_type>, "unsupported type.");

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

    QString inputType() const final {
      return InputType::SpinBox;
    }

    QString payload() const final {
      return Utils::quoted(Detail::MinValue) + ": " + QString::number(minValue) + ", " +
             Utils::quoted(Detail::MaxValue) + ": " + QString::number(maxValue);
    }

    bool isChoosable() const final {
      return false;
    }

    bool update(const QString& str) final {
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

    static_assert(std::is_floating_point_v<value_type>, "unsupported type.");

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

    QString inputType() const final {
      return InputType::DoubleSpinBox;
    }

    QString payload() const final {
      return Utils::quoted(Detail::MinValue) + ": " + QString::number(minValue, 'f', precision) +
             ", " + Utils::quoted(Detail::MaxValue) + ": " +
             QString::number(maxValue, 'f', precision) + ", " + Utils::quoted(Detail::Precision) +
             ": " + QString::number(precision);
    }

    bool isChoosable() const final {
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

    QString value() const final {
      return QString::number(qRadiansToDegrees(ref.value()), 'f', precision);
    }

    bool update(const QString& str) final {
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

    static_assert(std::is_integral_v<value_type>, "unsupported type.");

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

    QString inputType() const final {
      return InputType::Slider;
    }

    QString payload() const final {
      return Utils::quoted(Detail::MinValue) + ": " + QString::number(minValue) + ", " +
             Utils::quoted(Detail::MaxValue) + ": " + QString::number(maxValue);
    }

    bool isChoosable() const final {
      return false;
    }

    bool update(const QString& str) final {
      if (auto op = eval(str)) {
        if (minValue <= *op && *op <= maxValue) {
          setValue(*op);
          return true;
        }
      }
      return false;
    }
  };

  template <class B>
  class CheckBox : public ParameterType<B> {
   public:
    using value_type = typename Arg<B>::value_type;

   private:
    using ParameterType<B>::setValue;
    using ParameterType<B>::eval;
    using ParameterType<B>::ref;

   public:
    explicit CheckBox(Arg<B>& t_ref, const QString& t_about = "") :
        ParameterType<B>(t_ref, t_about) {
    }

    QString inputType() const final {
      return InputType::CheckBox;
    }

    QString payload() const final {
      return "";
    }

    bool isChoosable() const final {
      return true;
    }

    bool update(const QString& str) final {
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
    std::set<value_type> set;

   public:
    ComboBox(Arg<T>& t_ref, const QVector<value_type>& t_set, const QString& t_about = "") :
        ParameterType<T>(t_ref, t_about),
        set(t_set.begin(), t_set.end()) {
      if (!((set.size() > 1) && set.find(t_ref) != set.end())) {
        throw std::runtime_error("the size of set must be greater than 1, and must contain ref.");
      }
    }

    QString type() const final {
      return Utils::nameOfType<value_type>();
    }

    QString inputType() const final {
      return InputType::ComboBox;
    }

    QString payload() const final {
      QString options;
      QTextStream stream(&options);
      stream << Qt::fixed;

      for (auto it = set.begin(); it != set.end(); ++it) {
        const value_type& value = *it;
        if constexpr (std::is_base_of_v<QString, value_type>) {
          stream << Utils::quoted(value);
        } else if constexpr (std::is_enum_v<value_type>) {
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

    bool isChoosable() const final {
      return true;
    }

    bool update(const QString& str) final {
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

    QMap<value_type, QString> leftMap;
    QMap<QString, value_type> rightMap;

   public:
    MappedComboBox(Arg<T>& t_ref,
                   const QMap<value_type, QString>& t_map,
                   const QString& t_about = "") :
        ParameterType<T>(t_ref, t_about),
        leftMap(t_map),
        rightMap([&t_map]() {
          QMap<QString, value_type> map;
          for (auto it = t_map.begin(); it != t_map.end(); ++it) {
            map.insert(it.value(), it.key());
          }
          return map;
        }()) {
      bool contains = leftMap.find(t_ref) != leftMap.end();
      if (!((leftMap.size() > 1) && (static_cast<int>(leftMap.size()) == rightMap.size()) &&
            contains)) {
        throw std::runtime_error("the size of map must be greater than 1, and must contain ref.");
      }
    }

    QString value() const override {
      auto it = leftMap.find(ParameterType<T>::ref.value());
      if (it == leftMap.end()) {
        throw std::runtime_error("the value was not found.");
      } else {
        return Utils::quoted(it.value());
      }
    }

    QString inputType() const final {
      return InputType::ComboBox;
    }

    QString type() const final {
      return "mapped(" + Utils::nameOfType<value_type>() + ")";
    }

    QString payload() const final {
      QString options;
      QTextStream stream(&options);
      stream << Qt::fixed;

      for (auto it = rightMap.begin(); it != rightMap.end(); ++it) {
        stream << Utils::quoted(it.key());

        if (std::next(it) != rightMap.end()) {
          stream << ", ";
        }
      }
      options = "[" + options + "]";
      return Utils::quoted(Detail::Options) + ": " + options;
    }

    bool isChoosable() const final {
      return true;
    }

    bool update(const QString& str) final {
      if (auto it = rightMap.find(str); it != rightMap.end()) {
        setValue(it.value());
        return true;
      }
      return false;
    }
  };

  class PushButton : public ParameterBase {
    QString m_type;
    qulonglong m_parent;
    std::function<void()> m_function;
    QString m_about;

    void setUpdated(bool) final {
    }

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

    QString value() const final {
      return Utils::quoted(QString::number(reinterpret_cast<qulonglong>(&m_function)));
    }

    QString inputType() const final {
      return InputType::PushButton;
    }

    QString type() const final {
      return m_type;
    }

    QString description() const final {
      return m_about;
    }

    QString payload() const final {
      return Utils::quoted(Detail::Parent) + ": " + Utils::quoted(QString::number(m_parent));
    }

    bool isChoosable() const final {
      return false;
    }

    bool update(const QString&) final {
      return false;
    }
  };
} // namespace Parameters

#pragma clang diagnostic pop

#endif // SOCCER_COMMON_PARAMETERTYPE_H