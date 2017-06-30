#include <iostream>
#include <pv/pvData.h>
#include <pv/pvaClient.h>

using namespace std;
using namespace epics::pvData;
using namespace epics::pvaClient;

template <typename T>
T get(const PvaClientChannelPtr & channel)
{
	T value = NULL;
	
	PvaClientGetPtr get = channel->createGet("");
	PvaClientGetDataPtr getData = get->getData();
	
	PVStructurePtr pvStructure = getData->getPVStructure();
	if (pvStructure == NULL) {
		cout << "channel " << channel->getChannelName() << " : pvStructure is NULL\n";
		return value;
	}
	
	PVFieldPtr field = pvStructure->getSubField< PVScalarValue<T> >("value");
	if (field == NULL) {
		cout << "channel " << channel->getChannelName() << " : field is NULL\n";
		return value;
	}
		
	value = pvStructure->getSubField< PVScalarValue<T> >("value")->get();

	return value;
}

template <typename T>
bool put(const PvaClientChannelPtr & channel, const T & value)
{
	PvaClientPutPtr put = channel->createPut("");
	PvaClientPutDataPtr putData = put->getData();
	
	PVStructurePtr pvStructure = putData->getPVStructure();
	if (pvStructure == NULL) {
		cout << "channel " << channel->getChannelName() << " : pvStructure is NULL\n";
		return false;
	}
	
	PVFieldPtr field = pvStructure->getSubField< PVScalarValue<T> >("value");
	if (field == NULL) {
		cout << "channel " << channel->getChannelName() << " : field is NULL\n";
		return false;
	}
		
	pvStructure->getSubField< PVScalarValue<T> >("value")->put(value);

	put->put();

	return true;
}

int main (int argc, char **argv) 
{
	PvaClientPtr pva = PvaClient::get();

	string channel_name("PVRint");

	PvaClientChannelPtr channel = pva->channel(channel_name);

	int32_t val_int = get<int32_t>(channel);
	
	cout << "Before write\n";
	cout << "val: " << val_int << endl;
	
	put<int32_t>(channel, 69);	

	val_int = get<int32_t>(channel);
	
	cout << " After write\n";
	cout << "val: " << val_int << endl;

	return 0;
}
