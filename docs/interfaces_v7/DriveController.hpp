#pragma once

#include <memory>

class DriveControllerPimpl;

/// Interface to the drive hardware.
class DriveController
{
public:
	DriveController(const DriveController&) = delete;
	DriveController& operator=(const DriveController&) = delete;

	/// Get the singleton instance of the drive controller.
	static DriveController* getInstance();

	/// Set new speed and steering values for use with the PID controller.
	/// Use this outside of test mode for real drive usage.
	/// @param speed Percentage of max speed; range is -100 to 100.
	/// @param steering Percentage of steering; range is -100 to 100.
	/// @return true on success, false on failure.
	bool updateController(int speed, int steering);

	/// Set new speed and steering values bypassing the PID controller.
	/// Use this only in test mode when the vehicle's wheels don't touch the ground.
	/// @param speed Percentage of max speed; range is -100 to 100.
	/// @param steering Percentage of steering; range is -100 to 100.
	/// @return true on success, false on failure.
	bool updateDirect(int speed, int steering);

	/// Set new speed values for the motors bypassing the PID controller.
	/// Use this only in test mode when the vehicle's wheels don't touch the ground.
	/// @param speedLeft Percentage of max speed; range is -100 to 100.
	/// @param speedRight Percentage of max speed; range is -100 to 100.
	/// @return true on success, false on failure.
	bool updateDirectMotor(int speedLeft, int speedRight);

	/// Enable or disable test mode. Test mode will allow bypassing of the PID controller.
	/// Outside of test mode, the direct update functions are disabled.
	void setTestMode(bool enable);

	/// Get test mode state.
	bool getTestMode() const;

	/// Periodic update of the PID controllers. This has to be called once every 10ms.
	void step();

protected:
	DriveController();
	~DriveController();

	std::unique_ptr<DriveControllerPimpl> m_Pimpl;
};
