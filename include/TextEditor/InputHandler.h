/**
 * @parent include/TextEditor
 * @file InputHandler.h
 * @author ayano
 * @date 12/1/23
 * @brief
*/

#ifndef TEXTEDITOR_INPUTHANDLER_H
#define TEXTEDITOR_INPUTHANDLER_H

#include "KeyDefinition.h"
#include "ois/OIS.h"
#include "SingletonAbstract.hpp"
#include <unordered_map>

class InputHandler : public OIS::KeyListener, public OIS::MouseListener, public SingletonAbstract<InputHandler> {
    friend SingletonAbstract<InputHandler>;
public:
    virtual ~InputHandler();

    /**
     * add a key listener to the input handler
     * @param listener pointer to key listener
     * @param name name of the listener
     */
    void addKeyListener(OIS::KeyListener* listener, const std::string& name);
    /**
     * add a mouse listener to the inputmanager
     * @param listener pointer to mouse listener
     * @param name name of the listener
     */
    void addMouseListener(OIS::MouseListener* listener, const std::string& name);

    /**
     * remove a mouse listener from the input handler
     * @param name name of the listener set when adding it to the input handler
     */
    void removeMouseListener(const std::string& name);
    /**
     * remove a keyboard listener from the input handler
     * @param name name of the listener set when adding it to the input handler
     */
    void removeKeyListener(const std::string& name);
    /**
     * remove a mouse listener from the input handler
     * @param listener pointer to the mouse listener
     */
    void removeMouseListener(OIS::MouseListener* listener);
    /**
     * remove a keyboard listener from the inpur handler
     * @param listener pointer to the key listener
     */
    void removeKeyListener(OIS::KeyListener* listener);

    /**
     * set the input manager manually
     * @param manager input manager
     * @param name name of the input manager
     */
    void setInputManager(OIS::InputManager* manager, const std::string& name);
    /**
     * getter of input manager
     * @return current input manager
     */
    OIS::InputManager* getInputManager() const;

    /**
     * remove all mouse listener
     */
    void removeAllMouseListener();
    /**
     * remove all key listener
     */
    void removeAllKeyListener();
    /**
     * remove ALL listener
     */
    void removeAllListener();

private:

    bool keyPressed(const OIS::KeyEvent &arg) override;
    bool keyReleased(const OIS::KeyEvent &arg) override;
    bool mouseMoved(const OIS::MouseEvent &arg) override;
    bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id) override;
    bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id) override;

    InputHandler();

    OIS::Mouse* mouse;
    OIS::Keyboard* keyboard;

    OIS::KeyListener* key_listener;
    OIS::MouseListener* mouse_listener;
    OIS::InputManager* manager;

    std::unordered_map<std::string, OIS::KeyListener*> key_listener_map;
    std::unordered_map<std::string, OIS::MouseListener*> mouse_listener_map;

    std::vector<OIS::KeyListener*> key_listeners;
    std::vector<OIS::MouseListener*> mouse_listeners;
};


#endif //TEXTEDITOR_INPUTHANDLER_H
