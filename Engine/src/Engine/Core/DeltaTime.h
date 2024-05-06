#ifndef _DELTATIME_H_
#define _DELTATIME_H_

namespace Engine {

    class DeltaTime
    {
    public:
        DeltaTime(float time = 0.0f)
            : m_Time(time)
        {
        }

        operator float() const { return m_Time; }
        
        float GetSeconds() const { return m_Time; }
        float GetMilliSeconds() const { return m_Time * 1000.0f; }
    private:
        float m_Time;
    };
}

#endif // _DELTATIME_H_