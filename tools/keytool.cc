#include "keytool.h"
#include "privsend.h"
#include "utils.h"
#include "ulord.h"

using namespace std;

void NewKey(int argc, char const * argv[])
{
    try {
        CKeyExtension key(true);
        printf("Private Key: %s\nPublic Key: %s\nAddress : %s\n",
                key.ToString().c_str(),
                key.GetPubKeyString().c_str(),
                key.GetAddress().c_str());
    }
    catch(int) {
        printf("Create New Key failed!\n");
        return;
    }
    return;
}

void GenKey(int argc, char const * argv[])
{
    try {
        CKeyExtension key(false);
        printf("Masternode Key: %s\nPublic Key: %s\n",
                key.ToString().c_str(),
                key.GetPubKeyString().c_str());
    }
    catch(int) {
        printf("Create new masternode Key failed!\n");
        return;
    }
    return;
}

void ShowkeyHelp()
{
    cout << "Command \"keyshow\" example :" << endl << endl
        << "keyshow stringPrivkey" << endl
		<< "keyshow \"L1kF5amYLK6JZuuWyHTEk7dArcTu5nucFrGC9bUxmHezd8fdY183\"" << endl;
}
void Showkey(int argc, char const * argv[])
{
    if(argc < 3) {
        ShowkeyHelp();
        return;
    }
    string strpriv = argv[2];
    try {
        CKeyExtension key(strpriv);
        printf("Private Key: %s\nPublic Key: %s\nAddress : %s\nPubKey ID: %s\n",
                key.ToString().c_str(),
                key.GetPubKeyString().c_str(),
                key.GetAddress().c_str(),
                key.GetPubIdString().c_str());
    }
    catch(int) {
        printf("String(%s) is not a valid private key!\n", strpriv.c_str());
        return;
    }
    return;
}

void MatchkeyHelp()
{
    cout << "Command \"keymatch\" example :" << endl << endl
        << "keymatch stringPrivkey stringPubKey" << endl
		<< "keymatch \"L1kF5amYLK6JZuuWyHTEk7dArcTu5nucFrGC9bUxmHezd8fdY183\" \"03e867486ebaeeadda25f1e47612cdaad3384af49fa1242c5821b424937f8ec1f5\"" << endl;
}
void Matchkey(int argc, char const * argv[])
{
    if(argc < 4) {
        MatchkeyHelp();
        return;
    }
    string strpriv = argv[2];
    string strpub = argv[3];
    try {
        CKeyExtension key(strpriv);
        if(key.Match(strpub))
            printf("Matched key!\n");
        else
            printf("Don't Matched!\n");
    }
    catch(int) {
        printf("String(%s) is not a valid private key!\n", strpriv.c_str());
        return;
    }
    return;
}

void EncodekeyHelp()
{
    cout << "Command \"keyencode\" example :" << endl << endl
        << "keyencode stringPrivkey" << endl
		<< "keyencode \"L1kF5amYLK6JZuuWyHTEk7dArcTu5nucFrGC9bUxmHezd8fdY183\"" << endl;
}
void Encodekey(int argc, char const * argv[])
{
    if(argc < 3) {
        EncodekeyHelp();
        return;
    }
    string strpriv = argv[2];
    try {
        CKeyExtension key(strpriv);
        printf("Encode Key: %s\n", key.Encode().c_str());
    }
    catch(int) {
        printf("String(%s) is not a valid private key!\n", strpriv.c_str());
    }
    return;
}

void DecodekeyHelp()
{
    cout << "Command \"keydecode\" example :" << endl << endl
        << "keydecode stringPrivkey" << endl
		<< "keydecode \"L1kF5amYLK6JZuuWyHTEk7dArcTu5nucFrGC9bUxmHezd8fdY183\"" << endl;
}
void Decodekey(int argc, char const * argv[])
{
    if(argc < 3) {
        DecodekeyHelp();
        return;
    }
    string strpriv = argv[2];
    try {
        CKeyExtension key(1, strpriv);
        printf("Private Key: %s\nPublic Key: %s\nAddress : %s\n",
                key.ToString().c_str(),
                key.GetPubKeyString().c_str(),
                key.GetAddress().c_str());
    }
    catch(int) {
        printf("String(%s) is not a valid private key!\n", strpriv.c_str());
    }
    return;
}

void RecoverKeyHelp()
{
    cout << "Command \"keyrecover\" example :" << endl << endl
        << "keyrecover hash vSig" << endl
		<< "keyrecover \"hex\" \"string\"" << endl;
}
void RecoverKey(int argc, char const * argv[])
{
    if(argc < 4) {
        RecoverKeyHelp();
        return;
    }
    uint256 hash;
    hash.SetHex(argv[2]);

    bool fInvalid = false;
    vector<unsigned char> vchSigRcv = DecodeBase64(argv[3], &fInvalid);
    if (fInvalid) {
        cout << "decode failed vSig = " << argv[3] << endl;
        return;
    }

    CPubKey pubkeyFromSig;
    if(!pubkeyFromSig.RecoverCompact(hash, vchSigRcv)) {
        cout << "recover pubkey failed vSig = " << argv[3] << endl;
        return;
    }

    cout << "Recover pubkey = " << HexStr(pubkeyFromSig) << endl;
}

void ShowAddr(int argc, char const * argv[])
{
    if(argc < 3) {
        cout << "Command \"keyaddr\" example :" << endl << endl
        << "keyaddr address" << endl
		<< "keyaddr \"UjmXnfcffRvFe4Cp83p3Y3MVrxiX48P86z\"" << endl;
        return;
    }
    
    CBitcoinAddress address(argv[2]);
    if(address.IsValid()) {
        uint160 hashBytes;
        int type = 0;
        if (address.GetIndexKey(hashBytes, type)) {
            cout << "Hex: " << hashBytes.ToString() << endl;
            return;
        }
    }
    cout << "Invalid address!" << endl;
    return;
}