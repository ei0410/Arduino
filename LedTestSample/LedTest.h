#ifndef LedTest_h
#define LedTest_h

class LedTest {
  public:
    LedTest(int pin);
    void on();
    void off();

  private:
    int m_ledPin;
};

#endif
