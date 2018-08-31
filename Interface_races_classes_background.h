//
// Created by Oleg on 31.08.2018.
//

#ifndef ANOTHER_DND_SIMULATOR_INTERFACE_RACES_CLASSES_BACKGROUND_H
#define ANOTHER_DND_SIMULATOR_INTERFACE_RACES_CLASSES_BACKGROUND_H

class Features {
public:
    virtual void set(int) = 0;

    virtual void set(int, int, int, int) = 0;

    virtual int get() = 0;//
};

#endif //ANOTHER_DND_SIMULATOR_INTERFACE_RACES_CLASSES_BACKGROUND_H
