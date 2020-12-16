//
// Created by Александр on 02/10/2019.
//

#ifndef MY_DUMP_H
#define MY_DUMP_H

#define DUMP_INFO __FILE__, __PRETTY_FUNCTION__, __LINE__

/*!
 * Poor dump with message
 *
 * @param[in] "DUMP_INFO"
 * @param[in] flag message
 */

void dump(const char* file, const char* func, int line, const char* flag);

#endif // MY_DUMP_H