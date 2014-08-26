#include   "stdafx.h"  
   
  SECURITY_ATTRIBUTES   sa;  
  SECURITY_DESCRIPTOR   sd;  
  BYTE   aclBuffer[1024];  
  PACL   pacl   =   (PACL)&aclBuffer;  
  BYTE   sidBuffer[100];  
  PSID   psid   =   (PSID)&sidBuffer;  
  DWORD   sidBufferSize   =   100;  
  char   domainBuffer[80];  
  DWORD   domainBufferSize   =   80;  
  SID_NAME_USE   snu;  
  HANDLE   file;  
   
  LONG   result;  
  HKEY   regKey;  
  DWORD   disposition;  
  int   APIENTRY   WinMain(HINSTANCE   hInstance,  
                                            HINSTANCE   hPrevInstance,  
                                            LPSTR           lpCmdLine,  
                                            int               nCmdShow)  
  {  
    //   TODO:   Place   code   here.  
  ::InitializeSecurityDescriptor(&sd,SECURITY_DESCRIPTOR_REVISION);  
  ::InitializeAcl(pacl,1024,ACL_REVISION);  
  ::LookupAccountName(0,"guest",psid,&sidBufferSize,domainBuffer,  
  &domainBufferSize,&snu);  
  ::AddAccessAllowedAce(pacl,ACL_REVISION,GENERIC_READ|GENERIC_WRITE,psid);  
  ::SetSecurityDescriptorDacl(&sd,TRUE,pacl,FALSE);  
   
  sa.nLength   =   sizeof(SECURITY_ATTRIBUTES);  
  sa.bInheritHandle   =   FALSE;  
  sa.lpSecurityDescriptor   =   &sd;  
   
  file   =   ::CreateFile("d:\\testfile.txt",GENERIC_READ|GENERIC_WRITE,  
  0,&sa,CREATE_NEW,FILE_ATTRIBUTE_NORMAL,0);  
  ::CloseHandle(file);  
  return   0;  
  }  