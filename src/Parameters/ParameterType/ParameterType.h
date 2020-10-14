#ifndef PARAMETERTYPE_H
#define PARAMETERTYPE_H

#include <set>
#include <QString>
#include <QTextStream>
#include "Utils/Utils.h"
#include "MagicEnum/MagicEnum.h"

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
    static constexpr const char* Options = "Options";
    static constexpr const char* Regex = "Regex";
    static constexpr const char* Conditional = "Conditional";
  } // namespace Detail

  struct ParameterBase {
    virtual ~ParameterBase();
    virtual ParameterBase* clone() const = 0;
    virtual QString value() const = 0;
    virtual QString inputType() const = 0;
    virtual QString type() const = 0;
    virtual QString description() const = 0;
    virtual QString payload() const = 0;
    virtual bool isChooseable() const = 0;
    virtual void update(const QString& str) = 0;
  };

  template <class T>
  class ParameterType : public ParameterBase {
    static_assert(std::is_enum_v<T> || std::is_arithmetic_v<T> ||
                      std::is_same_v<T, QString>,
                  "unsuported type.");

   protected:
    T& ref;
    QString about;

   public:
    ParameterType(T& _ref, const QString& _about = "") :
        ref(_ref),
        about(_about) {
    }

    ~ParameterType() override {
    }

    ParameterType* clone() const override = 0;

    QString value() const override {
      QString str;
      if constexpr (std::is_enum_v<T>) {
        assert(MagicEnum::contains(ref));
        str = MagicEnum::name(ref);
      } else if constexpr (std::is_same_v<T, bool>) {
        str = ref ? "true" : "false";
      } else {
        QTextStream stream(&str);
        stream << ref;
      }

      if constexpr (std::is_arithmetic_v<T>) {
        return str;
      } else {
        return Utils::quoted(str);
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

    void update(const QString& str) override {
      if constexpr (std::is_enum_v<T>) {
        std::optional<T> op = MagicEnum::cast<T>(str);
        assert(op.has_value());
        ref = *op;
      } else if constexpr (std::is_same_v<T, bool>) {
        ref = QVariant(str).toBool();
      } else {
        QString buffer = str;
        QTextStream stream(&buffer);
        stream >> ref;
      }
    }
  };

  template <class T>
  class Text : public ParameterType<T> {
    QString regex;

   public:
    Text(T& _ref, const QString& _regex = ".*", const QString& _about = "") :
        ParameterType<T>(_ref, _about),
        regex(_regex) {
    }

    Text* clone() const override final {
      return new Text(*this);
    }

    QString inputType() const override final {
      return InputType::Text;
    }

    QString payload() const override final {
      return Utils::quoted(Detail::Regex) + ": " + Utils::quoted(regex);
    }

    bool isChooseable() const override final {
      return false;
    }
  };

  template <class T>
  class SpinBox : public ParameterType<T> {
    static_assert(std::is_arithmetic_v<T>, "unsupported type.");
    QString minValue;
    QString maxValue;

   public:
    SpinBox(T& _ref, T _minValue, T _maxValue, const QString& _about = "") :
        ParameterType<T>(_ref, _about) {
      assert(_minValue <= _ref && _ref <= _maxValue);
      QString buffer;
      QTextStream stream(&buffer);
      stream << _minValue << ' ' << _maxValue;
      stream >> minValue;
      stream >> maxValue;
    }

    SpinBox* clone() const override final {
      return new SpinBox(*this);
    }

    QString inputType() const override final {
      if constexpr (std::is_floating_point_v<T>) {
        return InputType::DoubleSpinBox;
      } else {
        return InputType::SpinBox;
      }
    }

    QString payload() const override final {
      return Utils::quoted(Detail::MinValue) + ": " + minValue + ", " +
             Utils::quoted(Detail::MaxValue) + ": " + maxValue;
    }

    bool isChooseable() const override final {
      return false;
    }
  };

  template <class T>
  class Slider : public ParameterType<T> {
    static_assert(std::is_integral_v<T>, "unsupported type.");
    QString minValue;
    QString maxValue;

   public:
    Slider(T& _ref, T _minValue, T _maxValue, const QString& _about = "") :
        ParameterType<T>(_ref, _about) {
      assert(_minValue <= _ref && _ref <= _maxValue);
      QString buffer;
      QTextStream stream(&buffer);
      stream << _minValue << ' ' << _maxValue;
      stream >> minValue;
      stream >> maxValue;
    }

    Slider* clone() const override final {
      return new Slider(*this);
    }

    QString inputType() const override final {
      return InputType::Slider;
    }

    QString payload() const override final {
      return Utils::quoted(Detail::MinValue) + ": " + minValue + ", " +
             Utils::quoted(Detail::MaxValue) + ": " + maxValue;
    }

    bool isChooseable() const override final {
      return false;
    }
  };

  class CheckBox : public ParameterType<bool> {
   public:
    CheckBox(bool& _ref, const QString& _about = "") :
        ParameterType<bool>(_ref, _about) {
    }

    CheckBox* clone() const override final {
      return new CheckBox(*this);
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
  };

  template <class T>
  class ComboBox : public ParameterType<T> {
    std::set<T> set;

   public:
    ComboBox(T& _ref, const QSet<T>& _set, const QString& _about = "") :
        ParameterType<T>(_ref, _about),
        set(_set.begin(), _set.end()) {
      assert(_set.size() > 1);
      assert(_set.contains(_ref));
    }

    ComboBox* clone() const override final {
      return new ComboBox(*this);
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

      for (T value : set) {
        if constexpr (std::is_same_v<T, QString>) {
          stream << Utils::quoted(value);
        } else if constexpr (std::is_enum_v<T>) {
          assert(MagicEnum::contains(value));
          stream << Utils::quoted(MagicEnum::name(value));
        } else {
          stream << value;
        }
        stream << " ";
      }

      options = "[" + options;
      options.back() = ']';
      return Utils::quoted(Detail::Options) + ": " + options.replace(" ", ", ");
    }

    bool isChooseable() const override final {
      return true;
    }
  };

  template <class T>
  class MappedComboBox : public ParameterType<T> {
    std::map<QString, T> map;

   public:
    MappedComboBox(T& _ref,
                   const QMap<T, QString>& _map,
                   const QString& _about = "") :
        ParameterType<T>(_ref, _about) {
      assert(_map.size() > 1);
      bool contains = false;
      for (auto& [key, value] : _map) {
        contains |= (value == _ref);
        map[value] = key;
      }
      assert(contains);
    }

    MappedComboBox* clone() const override final {
      return new MappedComboBox(*this);
    }

    QString value() const override {
      for (auto& [key, value] : map) {
        if (ParameterType<T>::ref == value) {
          return Utils::quoted(key);
        }
      }
      throw(std::runtime_error("the value was not found."));
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

      for (auto& [key, value] : map) {
        stream << Utils::quoted(key) << " ";
      }

      options = "[" + options;
      options.back() = ']';
      return Utils::quoted(Detail::Options) + ": " + options.replace(" ", ", ");
    }

    bool isChooseable() const override final {
      return true;
    }

    void update(const QString& str) override final {
      ParameterType<T>::ref = map[str];
    }
  };
} // namespace Parameters

#endif // PARAMETERTYPE_H
