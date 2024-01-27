#! /bin/sh

deviceList=bedroom_ac,dining_ac,living_couch_ac,living_window_ac,office_ac,guestroom_ac,childroom_ac
 
# Use comma as separator and apply as pattern
for d in ${deviceList//,/ }
do
#   esphome run ${d}.yml --no-logs
   esphome compile ${d}.yml
done