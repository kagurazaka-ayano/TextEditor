keys = "QWERTYUIOPASDFGHJKLZXCVBNM1234567890`-=[]\\;',./~!@#$%^&*()_+{}|:\"<>?"
numbers = ""


for i in keys:
    print(f"KEY_{i} = OIS::Keyboard::getAsKeyCode(\"{i}\"),")

