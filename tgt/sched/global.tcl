##############################################################
# $URL: http://memo.prisma/svn/tm/scriptProt/scheduler/tags/scheduler-1.17.0/global.tcl $
#
# $Author: federico $
#
# Description: GLOBAL UTILITIES FOR SCHEDULER
#
#
# $Rev: 8200 $
#
# $Date: 2005-05-19 11:52:44 +0200 (Thu, 19 May 2005) $
##############################################################

include "common/utils/generalUtils.tsm"

# NOTE: Obsolete file. All utilities procedures are collected in 
# files listed in /common/utils/

# Check Dependencies for Utilities Libraries
set scriptUtilsNeeded "scriptUtils-2.7.6"
if { [CheckCompatibility $scriptUtilsNeeded] == 0 } {
	logscr "Update of scriptUtils library ($scriptUtilsNeeded) is needed by current SMC library"
	exit
}

# All procedures have been moved in "common/utils/" directory
# in the following files:
include "common/utils/oldGeneralUtils.tsm"
include "common/utils/L3Utils.tsm"
