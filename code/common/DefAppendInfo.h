#ifndef __DefAppendInfo_H__
#define __DefAppendInfo_H__

#include <string>

const std::string STRING_APPENDINFO_ROOT = "hytera";
const std::string STRING_APPENDINFO_NAME = "appendinfo_name";

/************************************************************************/
/*                        ICC                                           */
/************************************************************************/
/*
<hytera>
    <appendinfo_name>icc_caseinfo_notice</appendinfo_name>
	<caseid>xxx</caseid>
	<callrefid>xxx</callrefid>
</hytera>
*/
const std::string ICC_STRING_APPENDINFO_CASEINFO_NOTICE = "icc_caseinfo_notice";
const std::string ICC_STRING_APPENDINFO_CASEINFO_NOTICE_CASEID = "caseid";
const std::string ICC_STRING_APPENDINFO_CASEINFO_NOTICE_CALLREFID = "callrefid";


/*
<hytera>
    <appendinfo_name>icc_callinfo_notice</appendinfo_name>
	<callid>xxx</callid>
	<callrefid>xxx</callrefid>
	<caller>xxx</caller>
	<called>xxx</called>
	<setuptime></setuptime>
	<disconnecttime></disconnecttime>
	<realcallrefid></realcallrefid>
	<refidtime></refidtime>
	<phonelist>
	    <phone></phone>
	<phonelist>	
</hytera>
*/

const std::string ICC_STRING_APPENDINFO_CALLINFO_NOTICE = "icc_callinfo_notice";
const std::string ICC_STRING_APPENDINFO_CALLINFO_NOTICE_CALLID = "callid";
const std::string ICC_STRING_APPENDINFO_CALLINFO_NOTICE_CALLREFID = "callrefid";
const std::string ICC_STRING_APPENDINFO_CALLINFO_NOTICE_CALLER = "caller";
const std::string ICC_STRING_APPENDINFO_CALLINFO_NOTICE_CALLED = "called";
const std::string ICC_STRING_APPENDINFO_CALLINFO_NOTICE_SETUPTIME = "setuptime";
const std::string ICC_STRING_APPENDINFO_CALLINFO_NOTICE_DISCONNECTTIME = "disconnecttime";
const std::string ICC_STRING_APPENDINFO_CALLINFO_NOTICE_REALCALLREFID = "realcallrefid";
const std::string ICC_STRING_APPENDINFO_CALLINFO_NOTICE_REFIDTIME = "refidtime";
const std::string ICC_STRING_APPENDINFO_CALLINFO_NOTICE_PHONELIST = "phonelist";
const std::string ICC_STRING_APPENDINFO_CALLINFO_NOTICE_PHONE = "phone";
const std::string ICC_STRING_APPENDINFO_CALLINFO_NOTICE_CASEID = "caseid";



/************************************************************************/
/*                LTE                                                   */
/************************************************************************/
/*
<hytera>
    <appendinfo_name>lte_updegrade_notice</appendinfo_name>
    <callid>xxx</callid>
	<updegradeflag></updegradeflag>//1:degrade 2:upgrade
	<timestamp></timestamp>
</hytera>
*/

const std::string LTE_STRING_APPENDINFO_UPDEGRADE_NOTICE = "lte_updegrade_notice";
const std::string LTE_STRING_APPENDINFO_UPDEGRADE_NOTICE_CALLID = "callid";
const std::string LTE_STRING_APPENDINFO_UPDEGRADE_NOTICE_UPDEGRADEFLAG = "updegradeflag";
const std::string LTE_STRING_APPENDINFO_UPDEGRADE_NOTICE_TIMESTAMP = "timestamp";

#endif