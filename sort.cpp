#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef unsigned long   u32;

int swap(int* pIntArray, int nFirstIndex, int nSecIndex)
{
	cout << "swap firstindex: "<< nFirstIndex << " nSecIndex: " << nSecIndex << endl;
	int nTempValue = pIntArray[nFirstIndex];
	pIntArray[nFirstIndex]=pIntArray[nSecIndex];
	pIntArray[nSecIndex]=nTempValue;
	return 0;
}

//array 元素个数为nSize
int BubbleSort(int* pIntArray, u32 nSize)
{
	int nExchangeCnt = 0;
	for ( u32 dwIndex = nSize; dwIndex>0; dwIndex-- )
	{
		bool bCheckExchange = false;
		for( u32 dwCompIndex = 0; dwCompIndex<(dwIndex-1); dwCompIndex++ )
		{
			if( pIntArray[dwCompIndex] > pIntArray[dwCompIndex+1] )
			{
				int nTmpValue = pIntArray[dwCompIndex];
				pIntArray[dwCompIndex]= pIntArray[dwCompIndex+1];
				pIntArray[dwCompIndex+1]= nTmpValue;			
				bCheckExchange = true;
			}
			nExchangeCnt++;
		}
		if( !bCheckExchange )
		{
			break;
		}
	}
	cout << "exchange count : " << nExchangeCnt << endl;
	return 0;
}


int SelectSort(int* pIntArray, u32 dwSize)
{
	for( u32 dwIndex = 0; dwIndex<dwSize; dwIndex++ )
	{
		u32 dwLeastIndex = dwIndex;
		for ( u32 dwCompIndex=dwIndex+1; dwCompIndex<dwSize; dwCompIndex++ )
		{
			if ( pIntArray[dwCompIndex] < pIntArray[dwLeastIndex] )
			{
				dwLeastIndex = dwCompIndex;
			}
		}
		
		if( dwLeastIndex != dwIndex )
		{
			int nTmpValue = pIntArray[dwIndex];
			pIntArray[dwIndex]=pIntArray[dwLeastIndex];
			pIntArray[dwLeastIndex] = nTmpValue;
		}
	}
	
	return 0;
}

int InsertSort(int* pIntArray, int nStartIndex, int nEndIndex)
{
	if( nEndIndex<= nStartIndex )
	{
		return 0;
	}
	for ( int nInserIndex = nStartIndex+1; nInserIndex<=nEndIndex; nInserIndex++ )
	{
		int nTempItemIndex = nInserIndex;
		while ( ((nTempItemIndex-1)>=nStartIndex) && ( pIntArray[nTempItemIndex] < pIntArray[nTempItemIndex-1]) )
		{
			swap( pIntArray, nTempItemIndex, nTempItemIndex-1 );
			nTempItemIndex--;
		}
	}
	return 0;
}

int InsertSort(int* pIntArray, u32 dwSize)
{
	for ( int nIndex = 1; nIndex<dwSize; nIndex++  )
	{
		int nTempValue = pIntArray[nIndex];
		
		cout <<  "nTempValue is " << nTempValue << endl;
		int i = 1;
		
		while ( (nIndex -i)>=0 && ( pIntArray[nIndex-i] > nTempValue ))
		{
			cout << "i = " << i << endl;
			pIntArray[nIndex-i+1] = pIntArray[nIndex-i];
			i++;
		}
		pIntArray[nIndex-i+1] = nTempValue;
	}	
	return 0;
}

int Merge(int* pArrayFirst, int nFirstSize, int* pArraySec, int nSecSize, int* pTemp)
{
	cout << "nFirstSize is " <<  nFirstSize << " nSecSize is "<< nSecSize << endl;
	int nFirstIndex = 0;
	int nSecIndex = 0;
	int nTempIndex = 0;
	while( nTempIndex <(nFirstSize+nSecSize) )
	{
		if ( nFirstIndex<nFirstSize && nSecIndex<nSecSize )
		{
			if ( pArrayFirst[nFirstIndex] > pArraySec[nSecIndex] )
			{
				pTemp[nTempIndex++] = pArraySec[nSecIndex];
				nSecIndex++;
			}
			else
			{
				pTemp[nTempIndex++] = pArrayFirst[nFirstIndex];
				nFirstIndex++;			
			}
			continue;
		}
		
		if ( nFirstIndex>=nFirstSize )
		{
			pTemp[nTempIndex++] = pArraySec[nSecIndex++];
			continue;
		}
		if ( nSecIndex>=nSecSize )
		{
			pTemp[nTempIndex++] = pArrayFirst[nFirstIndex++];
			continue;
		}
	}
	
	for( u32 i=0; i<(nFirstSize+nSecSize); i++ )
	{
		cout << " pTemp[ " << i << " ]" << " is " << pTemp[i] << endl;
		pArrayFirst[i]=pTemp[i];
	}
	return 0;
}

int MergeSort(int* pIntArray, u32 dwSize, int* pTemp)
{
	for ( u32 dwIndex = 0; dwIndex < dwSize ; dwIndex++ )
	{
		cout << "pIntArray["<<dwIndex<<"] is "<<pIntArray[dwIndex]<<endl;
	}
	if ( dwSize <= 1 )
	{
		return 0;
	}
	
	int nFirstSize = dwSize/2;
	
	MergeSort( pIntArray, nFirstSize, pTemp );
	MergeSort( pIntArray+nFirstSize, (dwSize-nFirstSize),pTemp);
	
	Merge( pIntArray,nFirstSize, pIntArray+nFirstSize, (dwSize-nFirstSize),pTemp );
	
	return 0;
}



int ShellSort(int* pIntArray, u32 dwSize)
{
	for ( int dwGap = dwSize/2; dwGap>0; dwGap=dwGap/2 )
	{
		for( int dwInsertIndex = dwGap; dwInsertIndex<dwSize; dwInsertIndex++ )
		{
			int dwArrayIndex = dwInsertIndex;
			while ( (dwArrayIndex-dwGap)>=0 && pIntArray[dwArrayIndex]<pIntArray[dwArrayIndex-dwGap])
			{
				swap(pIntArray, dwArrayIndex, dwArrayIndex-dwGap);
				dwArrayIndex-= dwGap;
			}
		}
	}
	return 0;
}

int heapAdjustItem( int* pIntArray, int nItemIndex, u32 dwSize )
{
	if( nItemIndex >= dwSize )
	{
		return 0;
	}
	
	int nMaxItemIndex = nItemIndex;
	
	//大顶堆判断
	int nLeftChildIndex = 2*nItemIndex + 1;
	int nRightChildIndex = 2*nItemIndex + 2;
	
	if( nLeftChildIndex < dwSize && pIntArray[nLeftChildIndex] > pIntArray[nMaxItemIndex] )
	{
		nMaxItemIndex = nLeftChildIndex;
	}
	if( nRightChildIndex<dwSize && pIntArray[nRightChildIndex]>pIntArray[nMaxItemIndex] )
	{
		nMaxItemIndex = nRightChildIndex;
	}
	
	if( nMaxItemIndex != nItemIndex )
	{
		int nTempItem = pIntArray[nItemIndex];
		pIntArray[nItemIndex]= pIntArray[nMaxItemIndex];
		pIntArray[nMaxItemIndex] = nTempItem;
		
		heapAdjustItem(pIntArray, nMaxItemIndex, dwSize);
	}
	return 0;
}

int HeapMaxForArray(int* pIntArray, int nSize)
{
	for ( int nIndex = nSize-1; nIndex>=0; nIndex-- )
	{
		heapAdjustItem( pIntArray, nIndex, nSize);
	}
	return 0;
}

int HeapSort(int* pIntArray, int dwSize)
{
	HeapMaxForArray( pIntArray, dwSize );
	
	for( int nIndex = 1; nIndex<dwSize; nIndex++ )
	{
		swap(pIntArray, 0, dwSize-nIndex);
		HeapMaxForArray(pIntArray, dwSize-nIndex);
	}
	return 0;
}




int QuickSort(int* pIntArray, int dwSize)
{
	if (  dwSize <= 1 )
	{
		cout << "size is "<< dwSize << " and return ! "<<endl; 
		return 0;
	}
	
	
	int nTempIndex = 0;
	int nBeginIndex = 0;
	int nEndIndex = dwSize-1;
	
	cout << "begin quick sort and size is "<< dwSize << endl;
	
	while( nEndIndex > nBeginIndex )
	{
		cout << "nEndIndex is " << nEndIndex << " nBeginIndex is "<< nBeginIndex << endl;
		if ( nTempIndex != nEndIndex )
		{
			if ( pIntArray[nEndIndex] < pIntArray[nTempIndex] )
			{
				swap(pIntArray, nEndIndex, nTempIndex);
				nTempIndex = nEndIndex;
				cout << "end compart nTempIndex is " << nTempIndex << endl;
			//	continue;
			}
			else
			{
				nEndIndex--;
				cout << "nEndIndex -- is "<< nEndIndex << endl;
				continue;
			}
		}
		if ( nTempIndex != nBeginIndex )
		{
			if ( pIntArray[nBeginIndex] > pIntArray[nTempIndex] )
			{
				swap(pIntArray, nBeginIndex, nTempIndex);
				nTempIndex = nBeginIndex;
				cout << "begin compart nTempIndex is " << nTempIndex << endl;
			//	continue;
			}
			else
			{
				nBeginIndex++;
				continue;
			}
		}
		//break;
	}
	
	QuickSort( pIntArray, nTempIndex );
	if ( nTempIndex != (dwSize-1) )
	{
		QuickSort( pIntArray+nTempIndex+1, dwSize-1-nTempIndex);
	}
	return 0;
}


void Reverse(string &A, int nLeftIndex, int nRightIndex)
{
	// Assert( nRightIndex>= nLeftIndex );
	// Assert( nRightIndex < A.length() );
	
	int l = nLeftIndex;
	int r = nRightIndex;
	while( l<r )
	{
		char temp = A[l];
		A[l++] = A[r];
		A[r--] = temp;
	}
}


void ReverseWord( string& A )
{
	Reverse(A, 0, A.length()-1);
	
	int nLeftIndex = -1;

	for( int i = 0; i<A.length(); i++ )
	{
		cout << "i is " << i << "char is " << A[i] << endl;
		if( A[i] != ' ' && nLeftIndex == -1 )
		{
			nLeftIndex = i;
		}
		if( A[i] == ' ' && nLeftIndex != -1 )
		{
			cout << "begin reverse and i is " << i << "nLeftIndex is "<< nLeftIndex << endl;
			Reverse(A, nLeftIndex, i-1);
			nLeftIndex = -1;
		}
	}
	return ;
}


bool StrAConstainStrB( string& A, string& B)
{
	int hash = 0;
	
	for( u32 i = 0; i<A.length(); i++ )
	{
		hash = hash | ( 1<<(A[i]-'A'));
	}
	
	for ( u32 j=0; j<B.length(); j++ )
	{
		if ( ( hash & (1<<(B[j]-'A')) )==0)
		{
			return false;
		}
	}
	return true;
}


void CollectStrSet( vector<string> & vec, string cStr, int nIndex )
{
	if( nIndex >= cStr.length() )
	{
		return ;
	}
}

int main(int argc, char* argv)
{
	int array[10] = {5, 7, 23, 76, 127, 320, 6, 9, 15, 22};
	
	cout << " insert sort ! " << endl;
	//int* pTemp = new int[10];
	InsertSort(array, 0, 9);
	
	string A="CDEFGabcef";
	string B="efEFOK";
	
	string C="I am a student.";
	
	cout << "A contain B is "<< StrAConstainStrB(A,B) << endl;
	
	ReverseWord(C);
	cout << "C reverse word is  "<< C.c_str() << endl;
	
	Reverse(A, 0, 9);
	cout << "Reverse A " << A.c_str() << endl; 
	
	for ( u32 dwIndex=0; dwIndex<10; dwIndex++ )
	{
		cout << array[dwIndex] << endl;
	}
	return 0;
}