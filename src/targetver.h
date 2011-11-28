
// Including SDKDDKVer.h defines the highest available Windows platform.

// If you wish to build your application for a previous Windows platform, include WinSDKVer.h and
// set the _WIN32_WINNT macro to the platform you wish to support before including SDKDDKVer.h.


#include <WinSDKVer.h>

// Target Windows 2000 & higher
#define WINVER 0x0500
#define _WIN32_WINNT 0x0500

// Speed up build process with minimal headers.
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN

#include <SDKDDKVer.h>