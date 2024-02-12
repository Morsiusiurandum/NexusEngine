#ifndef APP_H
#define APP_H
#include "Window.h"

class App
{
 public:
	App();
	
	auto Awake()   -> int;

 private:
	void Update();
	
	Window window_;
};

#endif//APP_H
