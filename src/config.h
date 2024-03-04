#pragma once

#define LOG

#ifdef LOG
#define LOG_TO_FILE
#ifdef LOG_TO_FILE
#define LOG_FILENAME "log.txt"
#endif
#endif
