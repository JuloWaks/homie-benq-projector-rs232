/*
BenQ Projector MQTT <-> RS232 controller based on the Homie MQTT convention
Copyright (C) 2018  Michel Peterson

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <Homie.h>

#include "main.hpp"


HomieNode projectorNode("benq", "projector");

void sendCommand(const String& command, const String& value) {
    Serial.print(SERIAL_HEAD);
    Serial.print(command);
    Serial.print(SERIAL_TOKEN);
    Serial.print(value);
    Serial.print(SERIAL_TRAIL);
}

bool powerHandler(const HomieRange& range, const String& value) {
    if (value != "on" && value != "off") {
        return false;
    }

    sendCommand("pow", value);
    projectorNode.setProperty("power").send(value);

    return true;
}

void setup() {
    Homie.disableLogging();
    Serial.begin(SERIAL_BAUD);
    Serial.swap();

    Homie_setFirmware(FW_NAME, FW_VERSION);
    Homie.setup();

    projectorNode.advertise("power").settable(powerHandler);
}

void loop() {
    Homie.loop();
}
