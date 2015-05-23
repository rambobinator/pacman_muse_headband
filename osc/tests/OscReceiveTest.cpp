/*
	oscpack -- Open Sound Control (OSC) packet manipulation library
    http://www.rossbencina.com/code/oscpack

    Copyright (c) 2004-2013 Ross Bencina <rossb@audiomulch.com>

	Permission is hereby granted, free of charge, to any person obtaining
	a copy of this software and associated documentation files
	(the "Software"), to deal in the Software without restriction,
	including without limitation the rights to use, copy, modify, merge,
	publish, distribute, sublicense, and/or sell copies of the Software,
	and to permit persons to whom the Software is furnished to do so,
	subject to the following conditions:

	The above copyright notice and this permission notice shall be
	included in all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
	MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
	IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
	ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
	CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
	WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/*
	The text above constitutes the entire oscpack license; however, 
	the oscpack developer(s) also make the following non-binding requests:

	Any person wishing to distribute modifications to the Software is
	requested to send the modifications to the original developer so that
	they can be incorporated into the canonical version. It is also 
	requested that these non-binding requests be included whenever the
	above license is reproduced.
*/
#include "OscReceiveTest.h"

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <ctime>
#include <cmath>

#if defined(__BORLANDC__) // workaround for BCB4 release build intrinsics bug
namespace std {
using ::__strcmp__;  // avoid error: E2316 '__strcmp__' is not a member of 'std'.
}
#endif

#include "osc/OscReceivedElements.h"

#include "ip/UdpSocket.h"
#include "osc/OscPacketListener.h"

extern int g_blink;
extern int g_berserk;

time_t      old_t = 0;

namespace osc{

class OscReceiveTestPacketListener : public OscPacketListener{
protected:

    void ProcessMessage( const osc::ReceivedMessage& m, 
            const IpEndpointName& remoteEndpoint )
    {
        (void) remoteEndpoint;
        try {
            // argument stream, and argument iterator, used in different
            // examples below.
            ReceivedMessageArgumentStream args = m.ArgumentStream();
            // ReceivedMessage::const_iterator arg = m.ArgumentsBegin();

            if( std::strcmp( m.AddressPattern(), "/muse/elements/blink" ) == 0 ){
                int     a;

                args >> a >> osc::EndMessage;
                if (a == 1){
                    g_blink = 1;
                    // std::cout << "received '/blink' message with arguments: "
                    //     << a << "\n";
                }
            }
            else if (std::strcmp( m.AddressPattern(), "/muse/elements/experimental/concentration" ) == 0){
                float   f;
                double  t;

                args >> f >> osc::EndMessage;
                if (old_t == 0)
                    old_t = time(NULL);
                if ((t = difftime(std::time(NULL), old_t)) > 3) { 
                    time(&old_t);
                    g_berserk = std::lroundf(f);
                }
                // std::cout << "received '/concentration' message with arguments: "
                //         << f << "\n";
            }
            else if (std::strcmp( m.AddressPattern(), "/muse/elements/experimental/mellow" ) == 0){
                float   f;

                args >> f >> osc::EndMessage;
                // std::cout << "received '/mellow' message with arguments: "
                //         << f << "\n";
            }
        }catch( Exception& e ){
            std::cout << "error while parsing message: "
                        << m.AddressPattern() << ": " << e.what() << "\n";
        }
    }    
};


void RunReceiveTest( int port )
{
    osc::OscReceiveTestPacketListener listener;
	UdpListeningReceiveSocket s(
            IpEndpointName( IpEndpointName::ANY_ADDRESS, port ),
            &listener );

	std::cout << "listening for input on port " << port << "...\n";
	std::cout << "press ctrl-c to end\n";

	s.RunUntilSigInt();

	std::cout << "finishing.\n";
}

} // namespace osc

#ifndef NO_OSC_TEST_MAIN

// int main(int argc, char* argv[])
// {
// 	if( argc >= 2 && std::strcmp( argv[1], "-h" ) == 0 ){
//         std::cout << "usage: OscReceiveTest [port]\n";
//         return 0;
//     }

// 	int port = 7000;

// 	if( argc >= 2 )
// 		port = std::atoi( argv[1] );

//     osc::RunReceiveTest( port );

//     return 0;
// }

#endif /* NO_OSC_TEST_MAIN */

