//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package abstract;

import abstract.*;
import global.*;

network CJDTG
{
    parameters:
        @display("bgb=800,600");
        double pktLossRate;
        double Copt @unit(mps);
        double BW @unit(bps);
        double MTU @unit(b);
        double jitter_mu;
        double jitter_sigma;
        double Dmin @unit(s);
        volatile double jitter @unit(s);
        
        int system_num;
        int var_num;
    submodules:
        globalObserver: GlobalObserver {
            @display("p=60,50");
        }
        underlayConfigurator: UnderlayConfigurator {
            @display("p=60,150");
        }
        supervisorySite: CloudNode {
            @display("p=195,285");
        }
        remoteSite: EdgeNode {
            @display("p=550,285");
        }
    connections allowunconnected:
}
