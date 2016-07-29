/*
 * PID.h
 *
 *  Created on: Jul 25, 2016
 *      Author: Emmanuel
 */

#ifndef PID_H_
#define PID_H_

extern void PID(uint32_t restangle, uint32_t offset,  uint32_t turning,  uint32_t dt);
extern void stopAndReset(void);



#endif /* PID_H_ */
