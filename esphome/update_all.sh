#! /bin/sh

deviceList=attic_high,attic_low,bedroom_ac,dining_ac,living_couch_ac,living_window_ac,office_ac,guestroom_ac,childroom_ac
 
# Use comma as separator and apply as pattern
for d in ${deviceList//,/ }
do
   esphome run ${d}.yml --no-logs
done