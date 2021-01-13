# Serial protocol for configuration

## Change config

`set <attribute> <value>\n`

`attribute` being
* id: (hopefully) unique device id
* height: height in room
* floor: which floor the device is in
* room: name of the room

alternatively

`set all id;height;floor;room\n`

## Read config

`get all`
