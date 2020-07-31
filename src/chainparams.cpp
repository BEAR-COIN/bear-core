// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2018-2020 The BEAR Coin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of //(0, uint256("0x001"))
    (0, uint256("00000fbf79eef95494f77e216840fe05e06c41b618188e5619a12940cee11d65"))
	;
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1596157200, // * UNIX timestamp of last checkpoint block
    0,    	    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    3000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    //1596157200,
    //0,
    //250
};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    //1596157200,
    //0,
    //100
};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params() const
{
    assert(this);
    static CBigNum bnTrustedModulus(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParams = libzerocoin::ZerocoinParams(bnTrustedModulus);

    return &ZCParams;
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x17;
        pchMessageStart[1] = 0x1b;
        pchMessageStart[2] = 0x54;
        pchMessageStart[3] = 0x1e;
        vAlertPubKey = ParseHex("04c085f3a0aab8f30d3f8bd299add07a17135bc33243a436c834201179b56cdab229fa05bb6d8b7648bf963cb0648b31c912ccaa25e06e876803ce9c90a30b2b14");
        nDefaultPort = 7171;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // BEAR starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 4000000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 2 * 60;
        nTargetSpacing = 2 * 60;
        nMaturity = 60;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 21000000 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 100;
        nModifierUpdateBlock = 1;
        nZerocoinStartHeight = 101;
        nAccumulatorStartHeight = 50;
        nZerocoinStartTime = 1529726034;
        nBlockEnforceSerialRange = 1;
        nBlockRecalculateAccumulators = ~1; 
        nBlockFirstFraudulent = ~1;
        nBlockLastGoodCheckpoint = ~1;

        const char* pszTimestamp = "If you’re a ʕ•ᴥ•ʔ, you get to hibernate. You do nothing for six months. Deal with it!";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("0443432f5f85dddcef709d5d9fdfa73975e46a18cfe97b1179ae99dcb622b6541c3515ff9f93c732961cf7dd7bba9d295cc09ace622f27ff21e9c888d031dc8633") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1596157200;
        genesis.nBits = 0x1E0FFFF0;
        genesis.nNonce = 709843;

		hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("00000fbf79eef95494f77e216840fe05e06c41b618188e5619a12940cee11d65"));
        assert(genesis.hashMerkleRoot == uint256("a96ce14106635aa786d9df0d1694352c989ed3601a3fa575e67e1af8b4c41b28"));

        // GC
        vSeeds.push_back(CDNSSeedData("104.155.166.208", "104.155.166.208"));
        vSeeds.push_back(CDNSSeedData("35.196.115.71", "35.196.115.71"));
        vSeeds.push_back(CDNSSeedData("34.82.197.183", "34.82.197.183"));
        vSeeds.push_back(CDNSSeedData("35.193.120.4", "35.193.120.4"));
        vSeeds.push_back(CDNSSeedData("34.73.214.156", "34.73.214.156"));
        vSeeds.push_back(CDNSSeedData("35.247.31.13", "35.247.31.13"));

        //Aruba
        vSeeds.push_back(CDNSSeedData("86.105.49.182", "86.105.49.182"));
        vSeeds.push_back(CDNSSeedData("89.36.217.175", "89.36.217.175"));

        // Scaleaway 
        vSeeds.push_back(CDNSSeedData("195.154.106.17", "195.154.106.17"));
        vSeeds.push_back(CDNSSeedData("51.159.64.121", "51.159.64.121"));

        // Noreithe 
        vSeeds.push_back(CDNSSeedData("91.205.172.86", "91.205.172.86"));

        // DNS SEEDER
        vSeeds.push_back(CDNSSeedData("dnsseeder.bearcoin.net", "dnsseeder.bearcoin.net"));
        vSeeds.push_back(CDNSSeedData("communityseeder.bearcoin.net", "communityseeder.bearcoin.net"));

        publicFundAddress = "bLq9hbmNAcHKnheBXJxh4mnMJs4c6xSaao";
        publicFundReward = 0.09 * COIN;
        publicFundStart = 1;

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 85); // 'b'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 90); // 'd'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 100); // 'h'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >(); // 'xpub'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >(); // 'xpriv'
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x02)(0x5e).convert_to_container<std::vector<unsigned char> >(); // '17'
        // #606 0x8000025e https://github.com/satoshilabs/slips/blob/master/slip-0044.md

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "0498239dd8368e6aad24b88aad3dcf51a2bd9a70fa0d7b7e8cc59cd17bf24fa52aa95e4a7795ec357e56a1a2b8691c2a0c39a08f4accb74d90bde6df8152603e6a";
        strObfuscationPoolDummyAddress = "bTpFYYmgAKR3mUBtA8cSXp4iKMPsiSwnrr";
        nStartMasternodePayments = 1516371317;

        /** Zerocoin */
        zerocoinModulus = "09967519546633664161786592116176188244477851735247464471262506936419821425521535537971729591952844"
            "7993474316710383495651554441492284699784318317920768642771782479156335915769589065125381511877736478656163146112"
            "0274778749282514833787626065783543239214817635079109932062526589069357037529741126387254431354640890113819012884"
            "5984727198875027923684216536572545251927687617204175968296261497488347174940599536643486971848573156659145626196"
            "7823585489859811013117353687337255659905995864128249363763371577762942618252152391331762957988146692582388256324"
            "83429163614150572996214543792012965484479369325464648385288082629456952";
        nMaxZerocoinSpendsPerTransaction = 7; 
        nMinZerocoinMintFee = 1 * ZCENT; 
        nMintRequiredConfirmations = 20; 
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100; 
        nZerocoinHeaderVersion = 4; 
        nBudget_Fee_Confirmations = 6; 

        nStakeMinConfirmations = 720;   
        nStakeMinAmount = 50 * COIN;    
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v1)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xfc;
        pchMessageStart[1] = 0xfa;
        pchMessageStart[2] = 0xfc;
        pchMessageStart[3] = 0xfd;
        vAlertPubKey = ParseHex("04e301a6c358aaa50a53c35a83527c8bbccd93436a78f5c4e3556afb0922c6c1b006afa2a165490d67bc0037d39026b57f4d4476f88c2b8ee5c6b2b9100533e6bb");
        nDefaultPort = 7123; 
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; 
        nTargetSpacing = 1 * 60;  
        nLastPOWBlock = 100;
        nBTChangeBlock = 1000;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 51197; 
        nMaxMoneyOut = 21000000 * COIN;
        nZerocoinStartHeight = 50;
        nZerocoinStartTime = 1529726039;
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = ~1; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = ~1; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = ~1; //Last valid accumulator checkpoint
        genesis.nTime = 1596157200;
        genesis.nNonce = 0;

	    hashGenesisBlock = genesis.GetHash();
	    //assert(hashGenesisBlock == uint256(""));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19); // '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239); // '9' or 'c'
        // Testnet bear BIP32 pubkeys
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x2a)(0x12)(0x11).convert_to_container<std::vector<unsigned char> >();
        // Testnet bear BIP32 prvkeys
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x41)(0x11)(0x1a).convert_to_container<std::vector<unsigned char> >();
        // Testnet bear BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "040f0abf9540f07fe5e4d3bb992951e14c23eb68515fcd9fbb089889e208ba16128e6e10b3000b86975f79c4f657615742a7e7a6c3ff044fd60e2b0947d565bedb";
        strObfuscationPoolDummyAddress = "xPL2qEEyCxm1VKdbxVo2KZCLygrXrMoGRv";
        nStartMasternodePayments = 1420837558;
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet

        nStakeMinConfirmations = 30;    // Required number of confirmations
        nStakeMinAmount = 1000 * COIN;  // Minimum required staking amount
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xe1;
        pchMessageStart[1] = 0xe2;
        pchMessageStart[2] = 0xe3;
        pchMessageStart[3] = 0xe4;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60;
        nTargetSpacing = 2 * 60;        
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1596157200;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 0;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 7321;
        //assert(hashGenesisBlock == uint256(""));

        vFixedSeeds.clear(); 
        vSeeds.clear();      

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 7321;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};

static CChainParams* pCurrentParams = 0;

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
