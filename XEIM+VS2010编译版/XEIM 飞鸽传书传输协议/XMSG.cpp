/* ���������Ϊ XEIM �ɸ봫�飬�� GPL ��ԴЭ�鱣�����κ�Υ����Э��������ǽ������Ŭ��׷���䷨�����Ρ�
XEIM �ɸ봫��ٷ���վ��http://www.freeeim.com/xeim/
XEIM �ɸ봫��ٷ���վ��http://bbs.freeeim.com/
*/
// XMSG.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "xtype.h"
#include "xdef.h"

void testXMSG()
{
	while(1)
	{
		XMSG xmsg;
		xmsg.m_nMessage = XEIMMSG_USERBAD;
		char *tmp = "Hello world.";
		xmsg.SetData(tmp, strlen(tmp)+1);

		XMSG msg2(xmsg.GetBuffer(), xmsg.GetBufferLength());

		printf("%s len:%d\n", msg2.GetData(), msg2.GetDataLenght());
		Sleep(100);
	}
}

int main(int argc, char* argv[])
{
	testXMSG();
/*	XMSG_SMS sms;
	sms.SetData("13798589047", "aaa", strlen("aaa")+1);
	char *tmp = sms.GetData();
	if (sms.m_dwIndex == 255)
	{
		XMSG_SMS tt(tmp);
		printf("%s\n", tt.GetBuffer());
	}*/
//	XMSG_SMS tt(tmp);
//	printf("%s\n%s\n", tt.GetNUM(), tt.GetBuffer());
	return 0;
}