#ifndef PIXEL_CLIENT_PROCESSOR
#define PIXEL_CLIENT_PROCESSOR

#include <pix/PixModel.h>

class PixProcessor {
public:
    
    /**
     * Runs the calibration process
     */
    virtual void onHome() = 0;

    /**
     * Runs the calibration process on the given pixel
     */
    virtual void onHome(unsigned char pixle) = 0;

    /**
     * Sets the soft limits for a given pixel
     */
    virtual void onSetLimit(unsigned char pixle, const PixLimit& limit) = 0;
    
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
     * Resets and clears any error codes on the board
     */
    virtual void onClearErrorCode() = 0;
    
    /**
     * Notifies that a ping request was made
     */
    virtual void requestPing() = 0;

    /**
     * Requests the number of pixels controlled by the board
     */
    virtual unsigned char requestPixels() = 0;

    /**
     * A request for the number of pixels currently moving on the board
     */
    virtual unsigned char requestMoving() = 0;

    /**
     * A request to see if a given pixel is currently moving
     */
    virtual bool requestIsMoving(unsigned char pixle) = 0;

    /**
     * Requests a pixel's target position in steps from zero (the destination position)
     */
    virtual int requestTargetSteps(unsigned char pixle) = 0;

    /**
     * Requests a pixel's current position in steps from zero (the position in transit)
     */
    virtual int requestSteps(unsigned char pixle) = 0;

    /**
     * Requests a pixel's current angle in degrees from zero (the destination angle)
     */
    virtual double requestTargetAngle(unsigned char pixle) = 0;
    
    /**
     * Requests a pixel's current angle in degrees from zero (the angle in transit)
     */
    virtual double requestAngle(unsigned char pixle) = 0;

    /**
     * Requests a pixel's current limit settings
     */
    virtual const PixLimit requestLimit(unsigned char pixle) = 0;

    /**
     * A request for a pixel's complete status (for debugging)
     */
    virtual const PixStatus requestStatus(unsigned char pixle) = 0;

    /**
     * A requests for the current error code (for debugging)
     */
    virtual int requestErrorCode() = 0;
};

#endif
