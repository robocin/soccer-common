#include "TestParameters.h"

TestParameters::TestParameters() {
}

TestParameters::~TestParameters() {
}

void TestParameters::initTestCase() {
}

void TestParameters::init() {
}

void TestParameters::cleanup() {
}

void TestParameters::cleanupTestCase() {
}

void TestParameters::
    test_ParameterType_eval_WithInvalidParameters_ShouldReturnNullopt() {
  using namespace Parameters;

  /* enum types */ {
    QCOMPARE(ParameterType<Args::MyEnum>::eval("a"), std::nullopt);
    QCOMPARE(ParameterType<Args::MyEnum>::eval("b"), std::nullopt);
    QCOMPARE(ParameterType<Args::MyEnum>::eval("c"), std::nullopt);
    QCOMPARE(ParameterType<Args::MyEnum>::eval("d"), std::nullopt);

    QCOMPARE(ParameterType<Args::MyEnum>::eval("aa"), std::nullopt);
    QCOMPARE(ParameterType<Args::MyEnum>::eval("bb"), std::nullopt);
    QCOMPARE(ParameterType<Args::MyEnum>::eval("cc"), std::nullopt);
    QCOMPARE(ParameterType<Args::MyEnum>::eval("dd"), std::nullopt);

    QCOMPARE(ParameterType<Args::MyEnum>::eval("Aa"), std::nullopt);
    QCOMPARE(ParameterType<Args::MyEnum>::eval("Bb"), std::nullopt);
    QCOMPARE(ParameterType<Args::MyEnum>::eval("Cc"), std::nullopt);
    QCOMPARE(ParameterType<Args::MyEnum>::eval("Dd"), std::nullopt);
  }

  /* boolean */ {
    QCOMPARE(ParameterType<bool>::eval("zero"), std::nullopt);
    QCOMPARE(ParameterType<bool>::eval("one"), std::nullopt);

    QCOMPARE(ParameterType<bool>::eval("-0"), std::nullopt);
    QCOMPARE(ParameterType<bool>::eval("-1"), std::nullopt);

    QCOMPARE(ParameterType<bool>::eval("FALSE"), std::nullopt);
    QCOMPARE(ParameterType<bool>::eval("TRUE"), std::nullopt);
  }

  /* arithmetic types */ {
    QCOMPARE(ParameterType<int16_t>::eval("one"), std::nullopt);
    QCOMPARE(ParameterType<int32_t>::eval("two"), std::nullopt);
    QCOMPARE(ParameterType<int64_t>::eval("three"), std::nullopt);
    QCOMPARE(ParameterType<float>::eval("four"), std::nullopt);
    QCOMPARE(ParameterType<double>::eval("five"), std::nullopt);

    QCOMPARE(ParameterType<uint16_t>::eval("one1"), std::nullopt);
    QCOMPARE(ParameterType<uint32_t>::eval("two2"), std::nullopt);
    QCOMPARE(ParameterType<uint64_t>::eval("three3"), std::nullopt);

    QCOMPARE(ParameterType<short>::eval("first"), std::nullopt);
    QCOMPARE(ParameterType<int>::eval("second"), std::nullopt);
    QCOMPARE(ParameterType<long>::eval("third"), std::nullopt);

    QCOMPARE(ParameterType<unsigned short>::eval("first1"), std::nullopt);
    QCOMPARE(ParameterType<unsigned int>::eval("second2"), std::nullopt);
    QCOMPARE(ParameterType<unsigned long>::eval("third3"), std::nullopt);
  }
}

void TestParameters::test_ParameterType_eval_WithValidParameters_ShouldWork() {
  using namespace Parameters;

  /* enum types */ {
    QCOMPARE(ParameterType<Args::MyEnum>::eval("A"), Args::MyEnum::A);
    QCOMPARE(ParameterType<Args::MyEnum>::eval("B"), Args::MyEnum::B);
    QCOMPARE(ParameterType<Args::MyEnum>::eval("C"), Args::MyEnum::C);
  }

  /* boolean */ {
    QCOMPARE(ParameterType<bool>::eval("0"), static_cast<bool>(0));
    QCOMPARE(ParameterType<bool>::eval("1"), static_cast<bool>(1));

    QCOMPARE(ParameterType<bool>::eval("false"), false);
    QCOMPARE(ParameterType<bool>::eval("true"), true);
  }

  /* arithmetic types */ {
    QCOMPARE(ParameterType<int16_t>::eval("-1"), static_cast<int16_t>(-1));
    QCOMPARE(ParameterType<int32_t>::eval("-2"), static_cast<int32_t>(-2));
    QCOMPARE(ParameterType<int64_t>::eval("-3"), static_cast<int64_t>(-3));
    QCOMPARE(ParameterType<float>::eval("-4.0"), static_cast<float>(-4));
    QCOMPARE(ParameterType<double>::eval("-5.0"), static_cast<double>(-5));

    QCOMPARE(ParameterType<uint16_t>::eval("1"), static_cast<uint16_t>(1));
    QCOMPARE(ParameterType<uint32_t>::eval("2"), static_cast<uint32_t>(2));
    QCOMPARE(ParameterType<uint64_t>::eval("3"), static_cast<uint64_t>(3));
    QCOMPARE(ParameterType<float>::eval("4.0"), static_cast<float>(4));
    QCOMPARE(ParameterType<double>::eval("5.0"), static_cast<double>(5));
  }

  /* QString (trivial) */ {
    QCOMPARE(ParameterType<QString>::eval("RobôCIn"), QString("RobôCIn"));
    QCOMPARE(ParameterType<QString>::eval("UFPE"), QString("UFPE"));
    QCOMPARE(ParameterType<QString>::eval("Barriguinha"),
             QString("Barriguinha"));
  }
}

void TestParameters::test_Text_WithValidParameters_ShouldConstruct() {
  using namespace Parameters;

  static constexpr const char* description = "antena de radio do curado";

  /* testing QString */ {
    Arg<QString> string = "sidney";
    auto text = Text(string, Regex::AnyMatch, description);
    QCOMPARE(text.value(), Utils::quoted("sidney"));
    QCOMPARE(text.type(), Utils::nameOfType<QString>());
    QCOMPARE(text.inputType(), InputType::Text);
    QCOMPARE(text.description(), description);
    QCOMPARE(text.payload(),
             Utils::quoted(Detail::Regex) + ": " +
                 Utils::quoted(Regex::AnyMatch.pattern()));
    QCOMPARE(text.isChooseable(), false);

    QCOMPARE(text.update("bordeaux"), true);
    QCOMPARE(string, "bordeaux");
  }

  /* testing integer */ {
    Arg<int> integer = 42;
    auto text = Text(integer, Regex::AnyMatch, description);
    QCOMPARE(text.value(), "42");
    QCOMPARE(text.type(), Utils::nameOfType<int>());
    QCOMPARE(text.inputType(), InputType::Text);
    QCOMPARE(text.description(), description);
    QCOMPARE(text.payload(),
             Utils::quoted(Detail::Regex) + ": " +
                 Utils::quoted(Regex::AnyMatch.pattern()));
    QCOMPARE(text.isChooseable(), false);

    QCOMPARE(text.update("24"), true);
    QCOMPARE(integer, 24);
    QCOMPARE(text.update("twenty-four"), false);
    QCOMPARE(integer, 24);
  }

  /* testing double */ {
    Arg<double> real = std::acos(-1.0);
    auto text = Text(real, Regex::AnyMatch, description);
    QCOMPARE(text.value(), QString::number(std::acos(-1.0), 'f', 10));
    QCOMPARE(text.type(), Utils::nameOfType<double>());
    QCOMPARE(text.inputType(), InputType::Text);
    QCOMPARE(text.description(), description);
    QCOMPARE(text.payload(),
             Utils::quoted(Detail::Regex) + ": " +
                 Utils::quoted(Regex::AnyMatch.pattern()));
    QCOMPARE(text.isChooseable(), false);

    QCOMPARE(text.update("3.33"), true);
    QCOMPARE(real, 3.33);
    QCOMPARE(text.update("abcde"), false);
    QCOMPARE(real, 3.33);
  }

  /* testing boolean */ {
    Arg<bool> boolean = false;
    auto text = Text(boolean, Regex::AnyMatch, description);
    QCOMPARE(text.value(), "false");
    QCOMPARE(text.type(), Utils::nameOfType<bool>());
    QCOMPARE(text.inputType(), InputType::Text);
    QCOMPARE(text.description(), description);
    QCOMPARE(text.payload(),
             Utils::quoted(Detail::Regex) + ": " +
                 Utils::quoted(Regex::AnyMatch.pattern()));
    QCOMPARE(text.isChooseable(), false);

    QCOMPARE(text.update("true"), true);
    QCOMPARE(boolean, true);
    QCOMPARE(text.update("VALOR_FALSO"), false);
    QCOMPARE(boolean, true);
  }
}

void TestParameters::test_Text_WithInvalidParameters_ShouldThrowException() {
  using namespace Parameters;

  /* testing QString */ {
    Arg<QString> empty;
    bool error = false;
    try {
      auto text = Text(empty, QRegularExpression(R"_((.+))_"));
    } catch (...) {
      error = true;
    }
    QVERIFY(error);
  }

  /* testing double */ {
    Arg<double> real = 1.234;
    bool error = false;
    try {
      auto text = Text(real, QRegularExpression(R"_(([a-z]+))_"));
    } catch (...) {
      error = true;
    }
    QVERIFY(error);
  }
}

void TestParameters::test_SpinBox_WithValidParameters_ShouldConstruct() {
  using namespace Parameters;

  static constexpr const char* description = "dale robocin";

  /* testing short */ {
    Arg<short> integer = 5;
    auto spinBox = SpinBox(integer, 0, 10, description);
    QCOMPARE(spinBox.value(), "5");
    QCOMPARE(spinBox.type(), Utils::nameOfType<short>());
    QCOMPARE(spinBox.inputType(), InputType::SpinBox);
    QCOMPARE(spinBox.description(), description);
    QCOMPARE(spinBox.payload(),
             Utils::quoted(Detail::MinValue) + ": " + QString::number(0) +
                 ", " + Utils::quoted(Detail::MaxValue) + ": " +
                 QString::number(10));
    QCOMPARE(spinBox.isChooseable(), false);
    QCOMPARE(spinBox.update("10"), true);
    QCOMPARE(integer, 10);
    QCOMPARE(spinBox.update("20"), false);
    QCOMPARE(integer, 10);
  }

  /* testing int */ {
    Arg<int> integer = 10;
    auto spinBox = SpinBox(integer, -10, 20, description);
    QCOMPARE(spinBox.value(), "10");
    QCOMPARE(spinBox.type(), Utils::nameOfType<int>());
    QCOMPARE(spinBox.inputType(), InputType::SpinBox);
    QCOMPARE(spinBox.description(), description);
    QCOMPARE(spinBox.payload(),
             Utils::quoted(Detail::MinValue) + ": " + QString::number(-10) +
                 ", " + Utils::quoted(Detail::MaxValue) + ": " +
                 QString::number(20));
    QCOMPARE(spinBox.isChooseable(), false);
    QCOMPARE(spinBox.update("15"), true);
    QCOMPARE(integer, 15);
    QCOMPARE(spinBox.update("30"), false);
    QCOMPARE(integer, 15);
  }

  /* testing long */ {
    Arg<long> integer = 20;
    auto spinBox = SpinBox(integer, -20, 30, description);
    QCOMPARE(spinBox.value(), "20");
    QCOMPARE(spinBox.type(), Utils::nameOfType<long>());
    QCOMPARE(spinBox.inputType(), InputType::SpinBox);
    QCOMPARE(spinBox.description(), description);
    QCOMPARE(spinBox.payload(),
             Utils::quoted(Detail::MinValue) + ": " + QString::number(-20) +
                 ", " + Utils::quoted(Detail::MaxValue) + ": " +
                 QString::number(30));
    QCOMPARE(spinBox.isChooseable(), false);
    QCOMPARE(spinBox.update("20"), true);
    QCOMPARE(integer, 20);
    QCOMPARE(spinBox.update("100"), false);
    QCOMPARE(integer, 20);
  }
}

void TestParameters::test_SpinBox_WithInvalidParameters_ShouldThrowException() {
  using namespace Parameters;

  /* testing short out of range */ {
    Arg<short> integer = 200;
    bool error = false;
    try {
      auto spinBox = SpinBox(integer, 0, 100);
    } catch (...) {
      error = true;
    }
    QVERIFY(error);
  }

  /* testing int wrong range */ {
    Arg<short> integer = 5;
    bool error = false;
    try {
      auto spinBox = SpinBox(integer, 10, -10);
    } catch (...) {
      error = true;
    }
    QVERIFY(error);
  }

  /* testing long out of range */ {
    Arg<long> integer = 10;
    bool error = false;
    try {
      auto spinBox = SpinBox(integer, 500, 1000);
    } catch (...) {
      error = true;
    }
    QVERIFY(error);
  }
}

void TestParameters::test_DoubleSpinBox_WithValidParameters_ShouldConstruct() {
  using namespace Parameters;

  static constexpr const char* description = "dale robocin";

  /* testing float */ {
    Arg<float> real = 5;
    auto doubleSpinBox = DoubleSpinBox(real, 0, 10, 6, description);
    QCOMPARE(doubleSpinBox.value(), "5.000000");
    QCOMPARE(doubleSpinBox.type(), Utils::nameOfType<float>());
    QCOMPARE(doubleSpinBox.inputType(), InputType::DoubleSpinBox);
    QCOMPARE(doubleSpinBox.description(), description);
    QCOMPARE(doubleSpinBox.payload(),
             Utils::quoted(Detail::MinValue) + ": " +
                 QString::number(0, 'f', 6) + ", " +
                 Utils::quoted(Detail::MaxValue) + ": " +
                 QString::number(10, 'f', 6) + ", " +
                 Utils::quoted(Detail::Precision) + ": " + QString::number(6));
    QCOMPARE(doubleSpinBox.isChooseable(), false);
    QCOMPARE(doubleSpinBox.update("10"), true);
    QCOMPARE(real, 10);
    QCOMPARE(doubleSpinBox.update("20"), false);
    QCOMPARE(real, 10);
  }

  /* testing double */ {
    Arg<double> real = 10;
    auto doubleSpinBox = DoubleSpinBox(real, -10, 20, 2, description);
    QCOMPARE(doubleSpinBox.value(), "10.00");
    QCOMPARE(doubleSpinBox.type(), Utils::nameOfType<double>());
    QCOMPARE(doubleSpinBox.inputType(), InputType::DoubleSpinBox);
    QCOMPARE(doubleSpinBox.description(), description);
    QCOMPARE(doubleSpinBox.payload(),
             Utils::quoted(Detail::MinValue) + ": " +
                 QString::number(-10, 'f', 2) + ", " +
                 Utils::quoted(Detail::MaxValue) + ": " +
                 QString::number(20, 'f', 2) + ", " +
                 Utils::quoted(Detail::Precision) + ": " + QString::number(2));
    QCOMPARE(doubleSpinBox.isChooseable(), false);
    QCOMPARE(doubleSpinBox.update("10"), true);
    QCOMPARE(real, 10);
    QCOMPARE(doubleSpinBox.update("40"), false);
    QCOMPARE(real, 10);
  }
}

void TestParameters::
    test_DoubleSpinBox_WithInvalidParameters_ShouldThrowException() {
  using namespace Parameters;

  /* testing float out of range */ {
    Arg<float> real = 200;
    bool error = false;
    try {
      auto doubleSpinBox = DoubleSpinBox(real, 0, 100);
    } catch (...) {
      error = true;
    }
    QVERIFY(error);
  }

  /* testing int wrong range */ {
    Arg<double> real = 5;
    bool error = false;
    try {
      auto doubleSpinBox = DoubleSpinBox(real, 10, -10);
    } catch (...) {
      error = true;
    }
    QVERIFY(error);
  }
}

void TestParameters::test_Slider_WithValidParameters_ShouldConstruct() {
  using namespace Parameters;

  static constexpr const char* description = "saudades dulle gourmet";

  /* testing short */ {
    Arg<short> integer = 5;
    auto slider = Slider(integer, 0, 10, description);
    QCOMPARE(slider.value(), "5");
    QCOMPARE(slider.type(), Utils::nameOfType<short>());
    QCOMPARE(slider.inputType(), InputType::Slider);
    QCOMPARE(slider.description(), description);
    QCOMPARE(slider.payload(),
             Utils::quoted(Detail::MinValue) + ": " + QString::number(0) +
                 ", " + Utils::quoted(Detail::MaxValue) + ": " +
                 QString::number(10));
    QCOMPARE(slider.isChooseable(), false);
    QCOMPARE(slider.update("10"), true);
    QCOMPARE(integer, 10);
    QCOMPARE(slider.update("20"), false);
    QCOMPARE(integer, 10);
  }

  /* testing int */ {
    Arg<int> integer = 10;
    auto slider = Slider(integer, -10, 20, description);
    QCOMPARE(slider.value(), "10");
    QCOMPARE(slider.type(), Utils::nameOfType<int>());
    QCOMPARE(slider.inputType(), InputType::Slider);
    QCOMPARE(slider.description(), description);
    QCOMPARE(slider.payload(),
             Utils::quoted(Detail::MinValue) + ": " + QString::number(-10) +
                 ", " + Utils::quoted(Detail::MaxValue) + ": " +
                 QString::number(20));
    QCOMPARE(slider.isChooseable(), false);
    QCOMPARE(slider.update("15"), true);
    QCOMPARE(integer, 15);
    QCOMPARE(slider.update("30"), false);
    QCOMPARE(integer, 15);
  }

  /* testing long */ {
    Arg<long> integer = 20;
    auto slider = Slider(integer, -20, 30, description);
    QCOMPARE(slider.value(), "20");
    QCOMPARE(slider.type(), Utils::nameOfType<long>());
    QCOMPARE(slider.inputType(), InputType::Slider);
    QCOMPARE(slider.description(), description);
    QCOMPARE(slider.payload(),
             Utils::quoted(Detail::MinValue) + ": " + QString::number(-20) +
                 ", " + Utils::quoted(Detail::MaxValue) + ": " +
                 QString::number(30));
    QCOMPARE(slider.isChooseable(), false);
    QCOMPARE(slider.update("20"), true);
    QCOMPARE(integer, 20);
    QCOMPARE(slider.update("100"), false);
    QCOMPARE(integer, 20);
  }
}

void TestParameters::test_Slider_WithInvalidParameters_ShouldThrowException() {
  using namespace Parameters;

  /* testing short out of range */ {
    Arg<short> integer = 200;
    bool error = false;
    try {
      auto slider = Slider(integer, 0, 100);
    } catch (...) {
      error = true;
    }
    QVERIFY(error);
  }

  /* testing int wrong range */ {
    Arg<short> integer = 5;
    bool error = false;
    try {
      auto slider = Slider(integer, 10, -10);
    } catch (...) {
      error = true;
    }
    QVERIFY(error);
  }

  /* testing long out of range */ {
    Arg<long> integer = 10;
    bool error = false;
    try {
      auto slider = Slider(integer, 500, 1000);
    } catch (...) {
      error = true;
    }
    QVERIFY(error);
  }
}

void TestParameters::test_CheckBox_WithValidParameters_ShouldConstruct() {
  using namespace Parameters;

  static constexpr const char* description = "imita uma moto plz";

  /* testing boolean */ {
    Arg<bool> boolean = false;
    auto checkBox = CheckBox(boolean, description);
    QCOMPARE(checkBox.value(), "false");
    QCOMPARE(checkBox.type(), Utils::nameOfType<bool>());
    QCOMPARE(checkBox.inputType(), InputType::CheckBox);
    QCOMPARE(checkBox.description(), description);
    QCOMPARE(checkBox.payload(), "");
    QCOMPARE(checkBox.isChooseable(), true);
    QCOMPARE(checkBox.update("true"), true);
    QCOMPARE(boolean, true);
    QCOMPARE(checkBox.update("ANY_VALUE"), false);
    QCOMPARE(boolean, true);
  }
}

void TestParameters::test_ComboBox_WithValidParameters_ShouldConstruct() {
  using namespace Parameters;

  static constexpr const char* description = "insira uma descricao aqui";

  /* testing enum */ {
    using Tp = Args::MyEnum;

    Arg<Tp> myEnum = Tp::A;
    auto comboBox = ComboBox(myEnum, {Tp::A, Tp::B, Tp::C}, description);
    QCOMPARE(comboBox.value(), Utils::quoted("A"));
    QCOMPARE(comboBox.type(), Utils::nameOfType<Tp>());
    QCOMPARE(comboBox.inputType(), InputType::ComboBox);
    QCOMPARE(comboBox.description(), description);
    QCOMPARE(comboBox.payload(),
             Utils::quoted(Detail::Options) + R"_(: ["A", "B", "C"])_");
    QCOMPARE(comboBox.isChooseable(), true);
    QCOMPARE(comboBox.update("B"), true);
    QCOMPARE(myEnum, Tp::B);
    QCOMPARE(comboBox.update("G"), false);
    QCOMPARE(myEnum, Tp::B);
  }

  /* testing QString */ {
    Arg<QString> string = "G";
    auto comboBox = ComboBox(string, {"G", "H", "I"}, description);
    QCOMPARE(comboBox.value(), Utils::quoted("G"));
    QCOMPARE(comboBox.type(), Utils::nameOfType<QString>());
    QCOMPARE(comboBox.inputType(), InputType::ComboBox);
    QCOMPARE(comboBox.description(), description);
    QCOMPARE(comboBox.payload(),
             Utils::quoted(Detail::Options) + R"_(: ["G", "H", "I"])_");
    QCOMPARE(comboBox.isChooseable(), true);
    QCOMPARE(comboBox.update("H"), true);
    QCOMPARE(string, "H");
    QCOMPARE(comboBox.update("Z"), false);
    QCOMPARE(string, "H");
  }

  /* testing int */ {
    Arg<int> integer = 11;
    auto comboBox = ComboBox(integer, {11, 12, 13, 14}, description);
    QCOMPARE(comboBox.value(), "11");
    QCOMPARE(comboBox.type(), Utils::nameOfType<int>());
    QCOMPARE(comboBox.inputType(), InputType::ComboBox);
    QCOMPARE(comboBox.description(), description);
    QCOMPARE(comboBox.payload(),
             Utils::quoted(Detail::Options) + R"_(: [11, 12, 13, 14])_");
    QCOMPARE(comboBox.isChooseable(), true);
    QCOMPARE(comboBox.update("13"), true);
    QCOMPARE(integer, 13);
    QCOMPARE(comboBox.update("20"), false);
    QCOMPARE(integer, 13);
  }
}

void TestParameters::
    test_ComboBox_WithInvalidParameters_ShouldThrowException() {
  using namespace Parameters;

  /* testing enum out of collection */ {
    using Tp = Args::MyEnum;

    Arg<Tp> myEnum = Tp::A;
    bool error = false;
    try {
      auto comboBox = ComboBox(myEnum, {Tp::B, Tp::C});
    } catch (...) {
      error = true;
    }
    QVERIFY(error);
  }

  /* testing QString few values */ {
    Arg<QString> string = "G";
    bool error = false;
    try {
      auto comboBox = ComboBox(string, {"G"});
    } catch (...) {
      error = true;
    }
    QVERIFY(error);
  }

  /* testing int out of collection */ {
    Arg<int> integer = 42;
    bool error = false;
    try {
      auto comboBox = ComboBox(integer, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    } catch (...) {
      error = true;
    }
    QVERIFY(error);
  }
}

void TestParameters::test_MappedComboBox_WithValidParameters_ShouldConstruct() {
  using namespace Parameters;

  static constexpr const char* description = "baviera, alemanha";

  /* testing enum */ {
    using Tp = Args::MyEnum;

    Arg<Tp> myEnum = Tp::A;
    auto mappedComboBox =
        MappedComboBox(myEnum,
                       {{Tp::A, "HAHA"}, {Tp::B, "HEHE"}, {Tp::C, "HIHI"}},
                       description);
    QCOMPARE(mappedComboBox.value(), Utils::quoted("HAHA"));
    QCOMPARE(mappedComboBox.type(), "mapped(" + Utils::nameOfType<Tp>() + ")");
    QCOMPARE(mappedComboBox.inputType(), InputType::ComboBox);
    QCOMPARE(mappedComboBox.description(), description);
    QCOMPARE(mappedComboBox.payload(),
             Utils::quoted(Detail::Options) +
                 R"_(: ["HAHA", "HEHE", "HIHI"])_");
    QCOMPARE(mappedComboBox.isChooseable(), true);
    QCOMPARE(mappedComboBox.update("HIHI"), true);
    QCOMPARE(myEnum, Tp::C);
    QCOMPARE(mappedComboBox.update("HOHO"), false);
    QCOMPARE(myEnum, Tp::C);
  }

  /* testing int */ {
    Arg<int> integer = 11;
    auto mappedComboBox =
        MappedComboBox(integer,
                       {{11, "11onze"}, {12, "12doze"}, {13, "13treze"}},
                       description);
    QCOMPARE(mappedComboBox.value(), Utils::quoted("11onze"));
    QCOMPARE(mappedComboBox.type(), "mapped(" + Utils::nameOfType<int>() + ")");
    QCOMPARE(mappedComboBox.inputType(), InputType::ComboBox);
    QCOMPARE(mappedComboBox.description(), description);
    QCOMPARE(mappedComboBox.payload(),
             Utils::quoted(Detail::Options) +
                 R"_(: ["11onze", "12doze", "13treze"])_");
    QCOMPARE(mappedComboBox.isChooseable(), true);
    QCOMPARE(mappedComboBox.update("13treze"), true);
    QCOMPARE(integer, 13);
    QCOMPARE(mappedComboBox.update("20vinte"), false);
    QCOMPARE(integer, 13);
  }
}

void TestParameters::
    test_MappedComboBox_WithInvalidParameters_ShouldThrowException() {
  using namespace Parameters;

  /* testing enum out of collection */ {
    using Tp = Args::MyEnum;

    Arg<Tp> myEnum = Tp::A;
    bool error = false;
    try {
      auto mappedComboBox =
          MappedComboBox(myEnum, {{Tp::B, "BLUE"}, {Tp::C, "COLOR"}});
    } catch (...) {
      error = true;
    }
    QVERIFY(error);
  }

  /* testing QString few values */ {
    Arg<QString> string = "G";
    bool error = false;
    try {
      auto mappedComboBox = MappedComboBox(string, {{"G", "GO ROBOCIN"}});
    } catch (...) {
      error = true;
    }
    QVERIFY(error);
  }

  /* testing int out of collection */ {
    Arg<int> integer = 42;
    bool error = false;
    try {
      auto mappedComboBox =
          MappedComboBox(integer, {{1, "one"}, {2, "two"}, {3, "three"}});
    } catch (...) {
      error = true;
    }
    QVERIFY(error);
  }
}

void TestParameters::
    test_ParametersHandler_WithValidParametersShouldConstruct() {
  using namespace Parameters;

  struct Args {
    Arg<bool> boolean = true;
    enum class Enum : int { A, B, C, D };
    Arg<Enum> enumeration = Enum::A;

    enum class Enum2 : int { A, B, C, D };
    Arg<Enum2> enumeration2 = Enum2::A;
    Arg<double> nested = 2.1;

    struct FirstLayer {
      Arg<int> integer = 10;
      Arg<double> real = std::acos(-1.0);
      Arg<QString> string = "parameter-type";
    };
    FirstLayer firstLayer;
  };
  Args args;

  Handler h;
  h["boolean"] = CheckBox(args.boolean);
  h["enumeration"] =
      ComboBox(args.enumeration, MagicEnum::values<Args::Enum>());

  h["enumeration2"] =
      MappedComboBox(args.enumeration2, MagicEnum::entries<Args::Enum2>());
  h["enumeration2"]["B"]["nested"] = DoubleSpinBox(args.nested, 0, 10);

  h["first-layer"]["integer"] = SpinBox(args.firstLayer.integer, 0, 20);
  h["first-layer"]["real"] =
      DoubleSpinBox(args.firstLayer.real, 0.0, 2.0 * std::acos(-1.0), 6);
  h["first-layer"]["string"] = Text(args.firstLayer.string);

  QJsonParseError error;
  QJsonDocument::fromJson(h.json(), &error);
  QCOMPARE(error.error, QJsonParseError::NoError);

  QCOMPARE(args.boolean, true);
  QCOMPARE(args.firstLayer.integer, 10);
  QCOMPARE(args.firstLayer.real, std::acos(-1.0));
  QCOMPARE(args.nested, 2.1);

  {
    QVector<UpdateRequest> updates;
    updates += UpdateRequest({"boolean"}, "false");
    updates += UpdateRequest({"first-layer", "integer"}, "7");
    updates += UpdateRequest({"first-layer", "real"}, "1.23456");
    updates += UpdateRequest({"enumeration2", "B", "nested"}, "4.2");
    h.update(updates);
  }

  QCOMPARE(args.boolean, false);
  QCOMPARE(args.firstLayer.integer, 7);
  QCOMPARE(args.firstLayer.real, 1.23456);
  QCOMPARE(args.nested, 4.2);

  /* testing JsonHandler::fromJsonObject and .get() */ {
    auto updates = JsonHandler::fromJsonObject(h.jsonObject()).updates();
    QVERIFY2(h.update(updates).isEmpty(), "Some updates were not made.");
  }

  /* testing JsonHandler::fromJsonObject and .update(), .get() */ {
    QVector<UpdateRequest> updates;
    updates += UpdateRequest({"boolean"}, "true");
    updates += UpdateRequest({"first-layer", "integer"}, "8");
    updates += UpdateRequest({"first-layer", "real"}, "2.23456");
    updates += UpdateRequest({"enumeration2", "B", "nested"}, "6.4");

    JsonHandler jh(JsonHandler::fromJsonObject(h.jsonObject()));
    jh.insert_or_assign(updates);
    updates = jh.updates();

    QVERIFY(h.update(updates).isEmpty());
  }
}

QTEST_MAIN(TestParameters)
