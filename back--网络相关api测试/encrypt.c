#define _CRT_GETPUTWCHAR_NOINLINE
#include "encrypt.h"
#include <stdio.h>  
#include <string.h>  
#include <conio.h>  
#include <wincrypt.h> 
#include <io.h>
#include "wing_malloc.h"

#define MY_ENCODING_TYPE  (PKCS_7_ASN_ENCODING | X509_ASN_ENCODING)  
#define KEYLENGTH  0x00800000  
#define ENCRYPT_ALGORITHM CALG_RC4   
#define ENCRYPT_BLOCK_SIZE 8   
 

HCRYPTKEY GenKeyByPassword(HCRYPTPROV hCryptProv,PCHAR szPassword);  
HCRYPTPROV GetCryptProv();    
/**
 *@�����ļ� szDestination����Ϊ�õ����ļ����ݣ���������ڴ棬���Զ�������� ʹ������Ҫdelete[] szDestination
 */
BOOL WingDecryptFile( PCHAR szSource, PCHAR &szDestination, PCHAR szPassword)   
{   
    FILE *hSource         = NULL;     
    HCRYPTPROV hCryptProv = 0;   
    HCRYPTKEY hKey        = 0;   
    PBYTE pbBuffer        = NULL;   
    size_t dwBlockLen     = 0;   
    DWORD dwBufferLen     = 0;   

    DWORD dwCount = 0;   
    int size      = 0;
   
    fopen_s( &hSource, szSource, "rb" );

	if( !hSource )
		return FALSE;
  
	size = _filelength(_fileno(hSource));
	

	szDestination = (PCHAR)wing_malloc( size+1 );
	if( !szDestination )
	{	
		fclose( hSource );  
		hSource = NULL;
		return 0;
	}

	memset( szDestination,0,size+1);

    hCryptProv = GetCryptProv(); 
	if( NULL == hCryptProv)
	{
		wing_free( szDestination );
		szDestination = NULL;
 
		fclose( hSource );  
		hSource = NULL;

		return  0;
	}

    hKey       = GenKeyByPassword( hCryptProv, szPassword);  

	if( NULL == hKey )
	{	

		CryptReleaseContext( hCryptProv, 0 );
		hCryptProv = NULL;

		wing_free(szDestination);
		szDestination = NULL;

		fclose(hSource); 
		hSource = NULL;
		
		return 0;
	}
      
    dwBlockLen  = 1000 - 1000 % ENCRYPT_BLOCK_SIZE;   
    dwBufferLen = dwBlockLen;   
 
  
    if(!(pbBuffer = (BYTE *)malloc(dwBufferLen)))  
    {  

		CryptDestroyKey( hKey );
		hKey = NULL;

		CryptReleaseContext( hCryptProv,0 ); 
		hCryptProv = NULL;
		 
		wing_free(szDestination);
		szDestination = NULL;

		fclose( hSource );   
		hSource = NULL;
		  
		return 0;  
    }  

	char *start = szDestination;
	
	size_t esize     = 1;
	size_t read_size = 0;

    do {   
        dwCount = fread( pbBuffer, esize , dwBlockLen, hSource );   
        if(ferror(hSource))  
        {  
			break;
        }  

        // ���� ����  
        if( !CryptDecrypt( hKey, 0, feof(hSource), 0, pbBuffer, &dwCount ))  
        {  
			break; 
        }  

		memcpy(start,pbBuffer,dwCount);
		
		start     += dwCount;
		read_size += dwCount;
		
		if( read_size >= (size_t)size ) 
			break;
		
    } while( !feof( hSource ) );   
  
    fclose( hSource );   
    hSource = NULL;
    
	wing_free( pbBuffer );
	pbBuffer = NULL;
	
    CryptDestroyKey( hKey ); 
    hKey = NULL;  
 
    CryptReleaseContext(hCryptProv, 0); 
    hCryptProv = NULL; 
  
    return TRUE;  
} 
  
   
/**
 * @����ԭ��szSource�ļ������ܺ�����ݴ洢��szDestination�ļ���   
 * @szSource��ԭ���ļ���  
 * @szDestination�����ܺ����ݴ洢�ļ�  
 * @szPassword���û���������� 
 */
BOOL WingEncryptFile( PCHAR szSource, PCHAR szDestination,  PCHAR szPassword)  
{  

    FILE *hSource      = NULL;   
    FILE *hDestination = NULL;   
  
    HCRYPTPROV hCryptProv = NULL;   
    HCRYPTKEY hKey        = NULL;   
  
    PBYTE pbBuffer    = NULL;   
    size_t dwBlockLen = NULL;   
    DWORD dwBufferLen = NULL;   
    DWORD dwCount     = NULL;   
   
	fopen_s( &hSource,szSource,"rb" );

	if( !hSource )
		return FALSE;

	fopen_s( &hDestination, szDestination, "wb" );

	if( !hDestination )
		return FALSE;

	size_t size = _filelength(_fileno(hSource));
  
    //��ȡ���ܷ����߾��  
    hCryptProv = GetCryptProv();  
	if( NULL == hCryptProv )
	{
		fclose( hSource );
		hSource = NULL;

		fclose( hDestination );
		hDestination = NULL;

		return 0;
	}
  
    hKey = GenKeyByPassword( hCryptProv, szPassword);  
	if( NULL == hKey )
	{
		fclose( hSource );
		hSource = NULL;

		fclose( hDestination );
		hDestination = NULL;

		CryptReleaseContext( hCryptProv, 0 );  
		hCryptProv = NULL;

		return  0;
	}
         
    // ��Ϊ�����㷨��ENCRYPT_BLOCK_SIZE ��С����ܣ����Ա����ܵ�  
    // ���ݳ��ȱ�����ENCRYPT_BLOCK_SIZE �����������������һ�μ��ܵ�  
    // ���ݳ��ȡ�  
  
    dwBlockLen = 1000 - 1000 % ENCRYPT_BLOCK_SIZE;   

    // ȷ�����ܺ��������ݿ��С. ���Ƿ�������ģʽ������������ɶ����Ŀռ�    

    if(ENCRYPT_BLOCK_SIZE > 1)   
        dwBufferLen = dwBlockLen + ENCRYPT_BLOCK_SIZE;   
    else   
        dwBufferLen = dwBlockLen;   
      
    // �����ڴ�ռ�.   
    if( !(pbBuffer = (BYTE *)wing_malloc(dwBufferLen)) )  
    {  
		fclose( hSource );
		hSource = NULL;

		fclose( hDestination );
		hDestination = NULL;

		CryptReleaseContext( hCryptProv, 0 );  
		hCryptProv = NULL;

        return 0;    
	}  
  
	size_t read_size = 0;

    do   
    {      
        dwCount = fread(pbBuffer, 1, dwBlockLen, hSource);   
        if( ferror(hSource) )  
        {   
            break;
        }  

        if(!CryptEncrypt(  
            hKey,           //��Կ  
            0,              //�������ͬʱ����ɢ�кͼ��ܣ����ﴫ��һ��ɢ�ж���  
            feof(hSource),  //��������һ�������ܵĿ飬����TRUE.�����������FALSE.  
                            //����ͨ���ж��Ƿ��ļ�β�������Ƿ�Ϊ���һ�顣  
            0,              //����  
            pbBuffer,       //���뱻�������ݣ�������ܺ������  
            &dwCount,       //���뱻��������ʵ�ʳ��ȣ�������ܺ����ݳ���  
            dwBufferLen))   //pbBuffer�Ĵ�С��  
        {   
           break;
        }   
  
        // �Ѽ��ܺ�����д�������ļ���   
  
        fwrite(pbBuffer, 1, dwCount, hDestination);   
        if(ferror(hDestination))  
        {   
            break;
        }  

		read_size += dwCount;
		if( read_size >= size ) 
			break;
  
    }   while(!feof(hSource));   
  


    fclose(hSource);
    hSource = NULL;
 
    fclose(hDestination); 
	hDestination = NULL;
  
	wing_free(pbBuffer); 
	pbBuffer = NULL;
	
    CryptDestroyKey(hKey);  
    hKey = NULL;
  
    CryptReleaseContext( hCryptProv, 0 );  
	hCryptProv = NULL;

    return 1;   
}
  
  
/**
 * @ ��ȡ�����ṩ�߾��
 */
HCRYPTPROV GetCryptProv()  
{  
    HCRYPTPROV hCryptProv;          

    if( !CryptAcquireContext( &hCryptProv, NULL,  MS_ENHANCED_PROV, PROV_RSA_FULL,  0) )
    {  
        if(!CryptAcquireContext(&hCryptProv, NULL, MS_ENHANCED_PROV, PROV_RSA_FULL, CRYPT_NEWKEYSET))  
        {  
           return NULL;  
        }  
    }  
    return hCryptProv;  
}  
 
  
HCRYPTKEY GenKeyByPassword(HCRYPTPROV hCryptProv,PCHAR szPassword)  
{  
    HCRYPTKEY hKey   = NULL;   
    HCRYPTHASH hHash = NULL;

	do{

		if( !CryptCreateHash( hCryptProv, CALG_MD5, 0, 0, &hHash ) )  
		{  
			break;
		}    

		if( !CryptHashData( hHash, (BYTE *)szPassword, (DWORD)strlen(szPassword), 0))  
		{  
			break;
		}  

		if( !CryptDeriveKey( hCryptProv, ENCRYPT_ALGORITHM, hHash, KEYLENGTH, &hKey ) )  
		{  
		   break;
		}  

	}while(0);

    if( hHash )   
    {  
        CryptDestroyHash(hHash);   
        hHash = 0;  
    }  
 
    return hKey;  
}  