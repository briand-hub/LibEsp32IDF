/** Copyright (C) 2023 brian_d (https://github.com/briand-hub)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <cstdio>

#include "BriandLibEsp32IDF.hxx""

using namespace std;

extern "C" void app_main(void)
{
    // Print out system info
    Briand::Esp32System::PrintInfo();

    // Instance a good wifi object
    unique_ptr<Briand::WifiManager> wifi = make_unique<Briand::WifiManager>();

    while (1) { 

        //
        // STATION EXAMPLE
        //

        // Connect to wifi as station
        wifi->ConnectStation("SSID", "PASSWORD", 5);

        // Wait 5 seconds
        vTaskDelay(5000 / portTICK_PERIOD_MS);

        // Disconnect
        wifi->DisonnectStation();

        //
        // ACCESS POINT EXAMPLE
        //

        // Start AP with


        // When station connects an handle could be called


        //
        // CONNECT STATION WHILE AP EXAMPLE
        //

        wifi->ConnectStation("SSID", "PASSWORD", 5);

        //
        // CLOSE AP
        //


        // Another time please!
        printf("\n\n***** ANOTHER ONE!\n\n");
    }
}