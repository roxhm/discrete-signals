// colores.h
#ifdef linux
//	#define FG_RED		"\e[31m"
	#define FG_BLACK	"\x1b[30m"
	#define FG_RED 		"\x1b[31m" 
	#define FG_GREEN 	"\x1b[32m" 
	#define FG_YELLOW 	"\x1b[33m" 
	#define FG_BLUE 	"\x1b[34m" 
	#define FG_MAGENTA 	"\x1b[35m" 
	#define FG_CYAN 	"\x1b[36m"
	#define FG_WHITE	"\x1b[37m"

	#define BG_BLACK	"\x1b[40m"
	#define BG_RED 		"\x1b[41m" 
	#define BG_GREEN 	"\x1b[42m" 
	#define BG_YELLOW 	"\x1b[43m" 
	#define BG_BLUE 	"\x1b[44m" 
	#define BG_MAGENTA 	"\x1b[45m" 
	#define BG_CYAN 	"\x1b[46m"
	#define BG_WHITE	"\x1b[47m"

	#define NONE 		"\x1b[0m" 

	#define BOLD		"\x1b[1m"
	#define ITALIC		"\x1b[3m"
	#define UNDERLINE	"\x1b[4m"
#else 
	#define FG_BLACK	""
	#define FG_RED 		"" 
	#define FG_GREEN 	"" 
	#define FG_YELLOW 	"" 
	#define FG_BLUE 	"" 
	#define FG_MAGENTA 	"" 
	#define FG_CYAN 	""
	#define FG_WHITE	""

	#define BOLD		""
	#define ITALIC		""
	#define UNDERLINE	""

	#define BG_BLACK	""
	#define BG_RED 		"" 
	#define BG_GREEN 	"" 
	#define BG_YELLOW 	"" 
	#define BG_BLUE 	"" 
	#define BG_MAGENTA 	"" 
	#define BG_CYAN 	""
	#define BG_WHITE	""
	
	#define NONE 		"" 
#endif
