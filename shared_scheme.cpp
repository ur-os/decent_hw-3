//
// Created by ur0s on 11/23/20.
//

#include "shared_scheme.h"

int split() {
    using namespace CryptoPP;

    std::string pubKey;
    int nShares, threshold;
    std::cin >> pubKey;
    std::cin >> nShares >> threshold;
    if(nShares < threshold || 2 > threshold) {
        std::cout << "Wrong arguments. Rule:\n\t 2 < T <= N\n";
        return -1;
    }


    AutoSeededRandomPool prng;
    ChannelSwitch *channelSwitch;
    StringSource source(pubKey, false, new SecretSharing(prng,
                                                         threshold, nShares, channelSwitch = new ChannelSwitch,true));
    std::vector<std::string> stringShares(nShares);
    vector_member_ptrs<StringSink> stringSinks(nShares);
    std::string channel;

      // load sinks in channels
    for (int i = 0; i < nShares; i++) {
        stringSinks[i].reset(new StringSink(stringShares[i]));
        channel = WordToString<word32>(i);
        stringSinks[i]->Put((byte *)channel.data(), 4);
        channelSwitch->AddRoute(channel, *stringSinks[i], DEFAULT_CHANNEL);
    }
      // process source to shares
    source.PumpAll();

    for(const auto& i: stringShares){
        std::cout << string_to_hex(i) << "\n";
    }
    return 0;
}

int recover() {
    using namespace CryptoPP;

    int threshold = 0;
    std::vector<std::string> stringShares;
    std::string in_buff;
    while (std::cin >> in_buff) {
        threshold++;
        stringShares.push_back(hex_to_string(in_buff));
    }


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

    while (strSources[0]->Pump(256))
        for (int i = 1; i < threshold; i++)
            strSources[i]->Pump(256);

    for (int i=0; i<threshold; i++)
        strSources[i]->PumpAll();

    std::cout << recovered;
    return 0;
}