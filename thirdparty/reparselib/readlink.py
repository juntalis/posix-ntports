from ctypes import *
from ctypes.wintypes import *
import sys, os

if len(sys.argv) == 1:
	print 'Usage: %s file' % sys.argv[0]
	sys.exit(0)

rlib = cdll.reparselib
outbuf = create_unicode_buffer(260)
for arg in sys.argv[1:]:
	fpath = LPCWSTR(os.path.abspath(arg))
	print '\nFile: %s' % arg
	print '  ReparsePointExists(%s)' % arg, rlib.ReparsePointExists(fpath) != 0
	print '  IsSymbolicLink(%s)' % arg, rlib.IsSymbolicLink(fpath) != 0
	print '  IsSymbolicLinkRelative(%s)' % arg, rlib.IsSymbolicLinkRelative(fpath) != 0
	print '  IsJunctionPoint(%s)' % arg, rlib.IsJunctionPoint(fpath) != 0
	print '  IsMountPoint(%s)' % arg, rlib.IsMountPoint(fpath) != 0
	memset(outbuf, 0, 260*sizeof(c_wchar))
	print '  GetPrintName(%s, outbuf, 260)' % arg, (rlib.GetPrintName(fpath, byref(outbuf), USHORT(260)) != 0)
	print '\toutbuf => %s' % outbuf.value
	memset(outbuf, 0, 260*sizeof(c_wchar))
	print '  GetSubstituteName(%s, outbuf, 260)' % arg, (rlib.GetSubstituteName(fpath, byref(outbuf), USHORT(260)) != 0)
	print '\toutbuf => %s' % outbuf.value