
#define BASE 2

uint32_t t = 0;

void setup()
{
    cli();
    for (int i = 0; i < 4; ++i) {
        pinMode(BASE+i, OUTPUT);
    }
    //set timer1 interrupt at 1Hz
    TCCR1A = 0;// set entire TCCR1A register to 0
    TCCR1B = 0;// same for TCCR1B
    TCNT1  = 0;//initialize counter value to 0
    // set compare match register for 1hz increments
    OCR1A = 363;// = (16*10^6) / (1*1024) - 1 (must be <65536)
    // turn on CTC mode
    TCCR1B |= (1 << WGM12);
    // enable timer compare interrupt
    TIMSK1 |= (1 << OCIE1A);
    sei();
}

ISR(TIMER1_COMPA_vect) {
    int value = (sin(2*3.14*440*t) + 1) * 8;
    for (int i = 0; i < 4; ++i) {
        digitalWrite(BASE+i, (value & 1) ? HIGH : LOW);
        value >>= 1;
    }
    t++;
}

void loop()
{
}
