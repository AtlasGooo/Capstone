#!/usr/bin/env python

'''
Author: Lin Zijun
Date: 2021-05-27 17:42:28
LastEditTime: 2021-05-27 19:08:31
LastEditors: Please set LastEditors
Description: In User Settings Edit
FilePath: /myturtlebot3/src/final_race/scripts/say.py
'''


import sys
import rospy
from sound_play.msg import SoundRequest
from sound_play.libsoundplay import SoundClient
from std_msgs.msg import String


if __name__ == '__main__':

    rospy.init_node('say', anonymous=True)
    rospy.loginfo("This is say node, which subscribe to /final_race/say")
    soundhandle = SoundClient()
    rospy.sleep(1)

    def callBack(msg):
        s = str(msg.data)
        voice = 'voice_kal_diphone'
        volume = 2.0

        rospy.loginfo('Saying: %s' % s)
        rospy.loginfo('Voice: %s' % voice)
        rospy.loginfo('Volume: %s' % volume)

        soundhandle.say(s, voice, volume)
        rospy.sleep(2)        


    rospy.Subscriber("/final_race/say",String,callBack)
    
    rospy.spin()


