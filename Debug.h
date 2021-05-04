#define ShoMessages 1 // 0 = off, 1 = on

// forget it; this doesn't work.

#include <iostream>

#if ShowMessages
#define MSG(X) cout << x << endl; // show messages
#else
#define MSG(X); // messages not shown
#endif
