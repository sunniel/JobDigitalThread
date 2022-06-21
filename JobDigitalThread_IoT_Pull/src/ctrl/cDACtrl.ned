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

package ctrl;

//
// TODO auto-generated module
//
simple cDACtrl
{
    parameters:
        @display("i=block/control");
        int var_num;
        int sample_len;
        double pull_threshold;
        double sigma_base;
        double sigma_max;
        double pull_beta;
        double pull_radix;
    gates:
        inout udplink;
        inout tcplink;
}
