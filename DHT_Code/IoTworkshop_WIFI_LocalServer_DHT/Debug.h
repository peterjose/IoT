/***************************************************
  @file   Debug.h
  @brief  File provides the functions for Debug
  @Author TeamRoboCET

  // IoT Workshop 2018
  // This is a demo code and shouldn't be used for any long term use or commercial purpose
***************************************************/

#ifndef _DEBUG_H_
#define _DEBUG_H_

#ifdef DEBUG_PRINT_ENABLE
  #define DEBUG_PRINT(x)                      Serial.print(x)
  #define DEBUG_PRINT_LN(x)                   Serial.println(x)
#else
  #define DEBUG_PRINT(x)
  #define DEBUG_PRINT_LN(x)
#endif /* DEBUG_PRINT_ENABLE */

#endif /* _DEBUG_H_ */
