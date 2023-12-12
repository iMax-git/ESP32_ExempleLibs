/**
 * All in one file - example for simulator
 * Développé par : Jan De Rudder (Merci !)
 */
class Button
{
public:
    enum Action { None, Pressed, Released, Repeat };

    using t_millis = unsigned long;

    static uint8_t const Auto;
    static t_millis const NoRepeat;

private:
    static t_millis mg_defaultDebounceDelay;

    uint8_t m_pin: 6;
    bool m_activeState: 1;
    bool m_lastState: 1;
    t_millis m_debounceDelay;
    t_millis m_lastStateTime = 0;
    t_millis m_lastRepeatTime = 0;

public:
    static void setDefaultDebounceDelay(t_millis delayMs);

    Button() = default;
    Button(uint8_t pin, uint8_t pinMode =INPUT, uint8_t activeState =Auto);

    void begin(uint8_t pin, uint8_t pinMode =INPUT, uint8_t activeState =Auto);

    Action read(t_millis repeatDelay=NoRepeat);

    void setDebounceDelay(t_millis delayMs);
};



// module level functions
////////////////////////////////////////////////////////////////////////////////
static uint8_t _activeStateForPinMode(uint8_t pinMode)
{
    if (pinMode == INPUT_PULLUP) {
        return LOW;
    } else {
        return HIGH;
    }
}


// class variables
////////////////////////////////////////////////////////////////////////////////
Button::t_millis Button::mg_defaultDebounceDelay = 50;
uint8_t const Button::Auto = 2;
Button::t_millis const Button::NoRepeat = (Button::t_millis)(-1);


// class methods
////////////////////////////////////////////////////////////////////////////////
void Button::setDefaultDebounceDelay(t_millis delayMs)
{
    mg_defaultDebounceDelay = delayMs;
}


// instance methods
////////////////////////////////////////////////////////////////////////////////
Button::Button(uint8_t pin, uint8_t pin_mode, uint8_t activeState)
{
    begin(pin, pin_mode, activeState);
}


void Button::begin(uint8_t pin, uint8_t pin_mode, uint8_t activeState)
{
    m_activeState = (activeState==Button::Auto) ?
        _activeStateForPinMode(pin_mode) : activeState;

    m_pin = pin;
    m_debounceDelay = mg_defaultDebounceDelay;

    pinMode(m_pin, pin_mode);
    delayMicroseconds(100);
    m_lastState = digitalRead(m_pin);
}


void Button::setDebounceDelay(t_millis delayMs)
{
    m_debounceDelay = delayMs;
}


////////////////////////////////////////////////////////////////////////////////
Button::Action Button::read(t_millis repeatDelay)
{
    Action action = None;
    t_millis const currTime = millis();

    if (currTime-m_lastStateTime > m_debounceDelay)
    {
        bool const currentState = digitalRead(m_pin);

        if (currentState != m_lastState)
        {
            if (m_lastState != m_activeState) {
                action = Pressed;
                m_lastRepeatTime = currTime;
            }
            else {
                action = Released;
            }
            m_lastState = currentState;
            m_lastStateTime = currTime;
        }
        else if (m_lastState == m_activeState
            && (currTime - m_lastRepeatTime) > repeatDelay)
        {
            action = Repeat;
            m_lastRepeatTime = currTime;
        }
    }
    return action;
}


////////////////////////////////////////////////////////////////////////////////
// program
////////////////////////////////////////////////////////////////////////////////
Button btn1(1, INPUT_PULLUP);
Button btn2(2, INPUT);

void setup()
{
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    btn1.setDebounceDelay(150);
}

void loop()
{
    Button::Action const b1Action = btn1.read(500);

    switch (b1Action) {
        case Button::Pressed:
            Serial.println("B1 pressed");
        break;
        case Button::Released:
            Serial.println("B1 released");
        break;
        case Button::Repeat:
            Serial.printf("B1 repeat (time: %lu)\n", millis());
        default:
        break;
    }

    auto const b2Action = btn2.read();

    if (b2Action == Button::Pressed) {
        digitalWrite(LED_BUILTIN, HIGH);
        Serial.println("B2 pressed");
    } else if (b2Action == Button::Released) {
        digitalWrite(LED_BUILTIN, LOW);
        Serial.println("B2 released");
    }

    delay(5);
}
