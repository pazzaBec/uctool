#include "ulord.h"
#include "ulordDB.h"


void MNHash(int argc, char const * argv[])
{
    if(argc < 7) {
        cout << "Command \"mnhash\" example :" << endl << endl
            << "mnhash txid voutid pubkey licensePeriod licenseVersion" << endl << endl;
        return;
    }

    CMNode mn;
    mn._txid = argv[2];
    mn._voutid = atoi(argv[3]);
    mn._pubkey = CPubKey(ParseHex(argv[4]));
    mn._licperiod = atoi64(argv[5]);
    mn._licversion = atoi(argv[6]);

    cout << mn.GetLicenseWord().ToString() << endl <<  mn.GetLicenseWord().GetHex() << endl << endl;
}

std::string ParseHex2String(const char* psz)
{
    std::vector<unsigned char> vch = ParseHex(psz);
    std::string res;
    res.insert(res.begin(), vch.begin(), vch.end());
    return res;
}
std::string ParseHex2String(const std::string str)
{
    return ParseHex2String(str.c_str());
}

void MNBoostUnSerialize(int argc, char const * argv[])
{
    if(argc < 3) {
        cout << "Command \"mnbstunseri\" example :" << endl << endl
            << "mnbstunseri HexString" << endl << endl;
        return;
    }
    string hex = string(argv[2]);
    string head = hex.substr(0,90);
    string version = hex.substr(90,8);
    string timestamp = hex.substr(98,16);
    string type = hex.substr(114,8);
    string txidlen = hex.substr(122,16);
    string txid = hex.substr(138,128);
    string voutid = hex.substr(266,8);
    
    cout << "Message Head: " << ParseHex2String(head) << endl
        << "Message version: " << Hex2Int(version) << endl
        << "Message timestamp: " << Hex2Int64(timestamp) << endl
        << "Message type: " << Hex2Int(type) << endl
        << "Message txid length: " << Hex2Int64(txidlen) << endl
        << "Message txid: " << ParseHex2String(txid) << endl
        << "Message voutid: " << Hex2Int(voutid) << endl;
}