//
// Created by ur0s on 11/23/20.
//

#include "shared_scheme.h"
std::vector<std::string> globalShares;

void split() {
    using namespace CryptoPP;

    std::string pubKey;
    int nShares, threshold;
    std::cin >> pubKey;
    std::cin >> nShares >> threshold;

    AutoSeededRandomPool prng;  // maybe wrong, need RandomPool rng;
    ChannelSwitch *channelSwitch;
    StringSource source(pubKey, false, new SecretSharing(prng,
                                                         threshold, nShares, channelSwitch = new ChannelSwitch,true));
    std::vector<std::string> stringShares(nShares);
    vector_member_ptrs<StringSink> stringSinks(nShares);
    std::string channel;

    for (int i = 0; i < nShares; i++) {
        stringSinks[i].reset(new StringSink(stringShares[i]));
        channel = WordToString<word32>(i);
        stringSinks[i]->Put((byte *)channel.data(), 4);
        channelSwitch->AddRoute(channel, *stringSinks[i], DEFAULT_CHANNEL);
    }

    source.PumpAll();
    for(auto i: stringShares){
        i = string_to_hex(i);
        globalShares.push_back(i);
        std::cout << i << "\n";
    }
}

void recover() {
    using namespace CryptoPP;

    int threshold = 0;
    std::vector<std::string> stringShares;
    std::string in_buff;
    while (std::cin >> in_buff) {
        threshold++;
        stringShares.push_back(hex_to_string(in_buff));
    }
//    for(const auto& i: stringShares)
//        std::cout << i << '\n';
//    std::cout << threshold << '\n';
//    for(auto i: globalShares) {
//        stringShares.push_back(hex_to_string(i));
//        threshold++;
//    }



    std::string channel;
    std::string recovered;
    SecretRecovery recovery(threshold, new StringSink(recovered));

    vector_member_ptrs<StringSource> strSources(threshold);
    channel.resize(4);

    for (int i=0; i < threshold; i++) {
        strSources[i].reset(new StringSource(stringShares[i], false));
        strSources[i]->Pump(4);
        strSources[i]->Get((byte*)&channel[0], 4);
        strSources[i]->Attach(new ChannelSwitch(recovery, channel));
    }

    while (strSources[0]->Pump(256)) {
        for (int i = 1; i < threshold; i++)
            strSources[i]->Pump(256);
    }

    for (int i=0; i<threshold; i++)
        strSources[i]->PumpAll();

    std::cout << recovered << "\n" << recovered.length();

}