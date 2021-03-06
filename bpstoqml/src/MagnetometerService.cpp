/* Copyright (c) 2012-2013 BlackBerry Limited.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include "MagnetometerService.hpp"
#include <iostream>

namespace bb {
namespace cascades {
namespace bps {

MagnetometerService::MagnetometerService(QObject *parent)
	: AbstractSensorService(SENSOR_TYPE_MAGNETOMETER, parent)
{
}

MagnetometerService::~MagnetometerService() {
}

void MagnetometerService::handleEvent(bps_event_t *event) {
	uint16_t code = bps_event_get_code(event);
	if (code == SENSOR_MAGNETOMETER_READING) {
		float x, y, z;
		sensor_event_get_xyz(event, &x, &y, &z);
		unsigned long long timestamp = getTimestamp(event);
		SensorAccuracy accuracy = getAccuracy(event);

		Q_EMIT magnetometerData(x, y, z, timestamp, accuracy);
	}
}

} /* namespace bps */
} /* namespace cascades */
} /* namespace bb */
