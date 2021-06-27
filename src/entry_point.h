#ifndef ENTRY_POINT_H
#define ENTRY_POINT_H

#define CREATE_APPLICATION(ClassName)       \
int main()                                  \
{                                           \
	Application * app = new ClassName();    \
	app->init();                            \
	app->run();                             \
	delete app;                             \
	return 0;                               \
}

#endif // ENTRY_POINT_H