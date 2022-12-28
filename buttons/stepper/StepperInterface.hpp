#ifndef __UIKIT_BUTTONS_STEPPER_INTERFACE__
#define __UIKIT_BUTTONS_STEPPER_INTERFACE__

class StepperInterface
{
public:
  virtual ~StepperInterface() {}
  virtual void onStepperValueChange(const char *id, int prev, int next, void *ptr = NULL) = 0;
};

#endif
