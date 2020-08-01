<p align="center"><img src="https://raw.githubusercontent.com/BEAR-COIN/branding/master/img/header.png" /></p>

# BEAR Core repository

## Coin specification:
<table>
<tr><td>Name</td><td>BEAR Coin</td></tr>
<tr><td>Ticker</td><td>BEAR</td></tr>
<tr><td>Masternode collateral</td><td>10 000 BEAR</td></tr>
<tr><td>Max coin supply</td><td>21 000 000 BEAR</td></tr>
<tr><td>Block time</td><td>120 seconds</td></tr>
<tr><td>Node/Masternode port</td><td>7171</td></tr>
<tr><td>RPC port</td><td>8181</td></tr>
<tr><td>Block reward</td><td>1 BEAR (flat block reward)</td></tr>
<tr><td>Staking (PoS) reward</td><td>1% (≈0.01 BEAR)</td></tr>
<tr><td>Masternode reward</td><td>90% (=0.90 BEAR)</td></tr>
<tr><td>Public fund</td><td>9%</td></tr>
</table>

By following parameters, we'll have:
* ≈ 21 600 newly created coins every month
* ≈ 216 coins - total monthly staking reward
* ≈ 19440 total monthly masternode reward for all active masternodes (example: ≈ 19440 / 300 active masternodes ≈ 64,8 BEAR coins montlhy each masternode)
* ≈ 1944 coins monthly will go to public fund.

Note: ≈ symbol mean "approximately equal to"

## Public fund
All expenses will be covered by public fund; however dynamic growth and additional development expenses can be achieved only if coin value will be much higher.

Example for better understanding: 
Let’s take BTC value ≈ 10 000 USD, in this case:
* if 1 BEAR coin value is 20 sats then 1944 BEAR ≈ 0.000388800 BTC ≈ 4 USD monthly ( ;(  )
* if 1 BEAR coin value is 200 sats then 1944 BEAR ≈ 0.003888000 BTC ≈ 40 USD monthly (after all we can cover basic maintenance monthly costs - servers, domains etc.. )
* if 1 BEAR coin value is 2 000 sats then 1944 BEAR ≈ 0.038880000 BTC ≈ 400 USD monthly (we can spend some money for promotion across internet - banners, blogs, youtubers to get new investors on board and that way increase value of coin)
* if 1 BEAR coin value is 20 000 sats then 1944 BEAR ≈ 0.388800000 BTC ≈ 4000 USD (we can hire new developers, create new apps and increase coin value by coin usability )
* sky is the limit...

Current value of BEAR Coin, actual stats of swap/coin/masternodes you will find on our website: [BEAR Coin](https://bearcoin.net/) All details about spending coins you will find in #public-fund text channel on [BEAR Coin Discord](https://bearcoin.net/go/discord).

## Installation
All binaries for different operating systems, you can download in the [releases repository](https://github.com/BEAR-COIN/bear-core/releases), however you can compile wallet from source codes. Recommended OS for compilation process is Ubuntu 16.04, compiled that way binaries will be working properly on Ubuntu 18, 19 and 20. If you dont have ubuntu 16.04 you can always install it on pendrive, VPS or Oracle VM VirtualBox.

***
Installation of libraries (using root user):

    add-apt-repository ppa:bitcoin/bitcoin -y
    apt-get update
    apt-get install -y build-essential libtool autotools-dev automake pkg-config libssl-dev libevent-dev bsdmainutils
    apt-get install -y libboost-system-dev libboost-filesystem-dev libboost-chrono-dev libboost-program-options-dev libboost-test-dev libboost-thread-dev
    apt-get install -y libdb4.8-dev libdb4.8++-dev

Cloning the repository and compiling (use any user with the sudo group):

    git clone https://github.com/BEAR-COIN/bear-core.git
    cd depends
    make HOST=x86_64-pc-linux-gnu
    cd ..
    make clean
    ./autogen.sh
    ./configure --prefix=`pwd`/depends/x86_64-pc-linux-gnu
    sudo make
    
Compiled binaries you can find in /src and src/qt folders.
    
Running the daemon:

    ./beard 

Stopping the daemon:

    ./bear-cli stop

Demon status:

    ./bear-cli getinfo

Additionally you can compile wallet for Windows by following steps:

    sudo apt install g++-mingw-w64-x86-64

    cd depends
    make HOST=i686-w64-mingw32
    cd ..
    make clean
    ./autogen.sh
    ./configure --prefix=`pwd`/depends/i686-w64-mingw32
    sudo make

***

## Security
If you discover a security vulnerability or any other issue within this package, please send an e-mail to contact@bearcoin.net

## Credits
This project exists thanks to all the people who [contribute](../../contributors).

## License
Distributed under the MIT software license, see the accompanying file [COPYING](COPYING) or [MIT software license](http://www.opensource.org/licenses/mit-license.php)
BEAR Coin uses components from PIVX Core, which uses components of both Bitcoin and DASH.
© [BEAR Coin](https://bearcoin.net/)