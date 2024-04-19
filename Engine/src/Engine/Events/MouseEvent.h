#ifndef _MOUSEEVENT_H_
#define _MOUSEEVENT_H_

#include "../../Enpch.h"
#include "Event.h"

namespace Engine {

    class ENGINE_API MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(float x, float y)
            : m_MouseX(x), m_MouseY(y) {}
        
        inline float GetX() const { return m_MouseX; }
        inline float GetY() const { return m_MouseY; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseMoved)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
    private:
        float m_MouseX, m_MouseY;
    };

    class ENGINE_API MouseScrolledEvent : public Event
    {
    public:
        MouseScrolledEvent(float xoffset, float yoffset)
            : m_XOffSet(xoffset), m_YOffSet(yoffset) {}
        
        inline float GetXOffSet() const { return m_XOffSet; }
        inline float GetYOffSet() const { return m_YOffSet; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << m_XOffSet << ", " << m_YOffSet;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseScrolled)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
    private:
        float m_XOffSet, m_YOffSet;
    };

    class ENGINE_API MouseButtonEvent : public Event
    {
    public:
        inline int GetMouseButton() const { return m_Button; }

        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
    protected:
        MouseButtonEvent(int button)
            : m_Button(button) {}
        int m_Button;
    };

    class ENGINE_API MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(int button)
            : MouseButtonEvent(button) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << m_Button;
            return ss.str();
        } 

        EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    class ENGINE_API MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(int button)
            : MouseButtonEvent(button) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << m_Button;
            return ss.str();
        } 

        EVENT_CLASS_TYPE(MouseButtonReleased)
    };
}

#endif // _MOUSEEVENT_H_