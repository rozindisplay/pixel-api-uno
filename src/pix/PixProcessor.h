#ifndef PIXEL_CLIENT_PROCESSOR
#define PIXEL_CLIENT_PROCESSOR

#include <pix/PixModel.h>

class PixProcessor {
public:
    /**
     * Sets the soft limits for all of the pixels and runs the calibration process
     */
    virtual void onInit(const Limit& limitP0, const Limit& limitP1, const Limit& limitP2, const Limit& limitP3) = 0;
    
    /**
     * Runs the calibration process
     */
    virtual void onHome() = 0;

    /**
     * Resets and clears the error code
     */
    virtual void onClearErrorCode() = 0;

    /**
     * Sets the soft limits for a given pixel
     */
    virtual void onSetLimit(unsigned char pixle, const Limit& limit) = 0;
    
    /**
     * Sets a pixel position using steps as the unit
     */
    virtual void onSetSteps(unsigned char pixle, int steps) = 0;

    /**
     * Adds the given number of steps to the current position
     */
    virtual void onAddSteps(unsigned char pixle, int steps) = 0;

    /**
     * Sets the pixel position using the angle (in degrees) as the unit
     */
    virtual void onSetAngle(unsigned char pixle, double angle) = 0;

    /**
     * Adds the given angle (in degrees) to the current position
     */
    virtual void onAddAngle(unsigned char pixle, double angle) = 0;
    
    /**
     * Notifies that a ping request was made
     */
    virtual void requestPing() = 0;

    /**
     * A requests for the current error code
     */
    virtual int requestErrorCode() = 0;

    /**
     * A request for the number of moving pixels
     */
    virtual unsigned char requestMovingCount() = 0;

    /**
     * A request for the node's complete status
     */
    virtual const NodeStatus requestStatus() = 0;
};

#endif
