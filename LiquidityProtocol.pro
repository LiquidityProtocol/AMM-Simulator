QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ui/AccountListWidgetItem.cpp \
    ui/ArbitrageurSimulationGraphItem.cpp \
    ui/ExistingPoolProvisionDialog.cpp \
    ui/ManualPlayground.cpp \
    ui/MintDialog.cpp \
    ui/NewMainWindow.cpp \
    ui/NewPoolProvisionDialog.cpp \
    ui/PoolGraphItem.cpp \
    ui/PoolListWidgetItem.cpp \
    ui/PoolTokenDialog.cpp \
    ui/PoolTokenListWidgetItem.cpp \
    ui/ProvideDialog.cpp \
    ui/ProviderSimulationGraphItem.cpp \
    ui/SimulationPlayground.cpp \
    ui/TokenListWidgetItem.cpp \
    ui/TradeDialog.cpp \
    ui/WalletListWidgetItem.cpp \
    ui/WithdrawDialog.cpp \
    ui/introductorywindow.cpp \
    ui/main.cpp \
    qcustomplot.cpp \
    src/Market/Agents/Arbitrager.cpp \
    src/Market/Agents/Provider.cpp \
    src/Market/Infrastructure/Signals.cpp \
    src/Market/Infrastructure/SignalsHandler.cpp \
    src/Market/Simulation.cpp \
    src/Utilities/Account.cpp \
    src/Utilities/Operation.cpp \
    src/Utilities/PoolEpochData.cpp \
    src/Utilities/PoolInterface.cpp \
    src/Utilities/Token.cpp \
    src/Utilities/TokensContainer.cpp \
    src/Protocols/CurvePool.cpp \
    src/Protocols/Protocols.cpp \
    src/Playground.cpp \
    src/Market/Infrastructure/Market.cpp \
    src/Market/Infrastructure/CommunityActor.cpp \
    src/Utilities/Utilities.cpp

HEADERS += \
    ui/AccountListWidgetItem.h \
    ui/ArbitrageurSimulationGraphItem.h \
    ui/ExistingPoolProvisionDialog.h \
    ui/ManualPlayground.h \
    ui/MintDialog.h \
    ui/NewMainWindow.h \
    ui/NewPoolProvisionDialog.h \
    ui/PoolGraphItem.h \
    ui/PoolListWidgetItem.h \
    ui/PoolTokenDialog.h \
    ui/PoolTokenListWidgetItem.h \
    ui/ProvideDialog.h \
    ui/ProviderSimulationGraphItem.h \
    ui/SimulationPlayground.h \
    ui/TokenListWidgetItem.h \
    ui/TradeDialog.h \
    ui/WalletListWidgetItem.h \
    ui/introductorywindow.h \
    qcustomplot.h \
    ui/WithdrawDialog.h \
    src/Market/Agents/Arbitrager.hpp \
    src/Market/Agents/Provider.hpp \
    src/Market/Infrastructure/Signals.hpp \
    src/Market/Infrastructure/SignalsHandler.hpp \
    src/Market/Simulation.hpp \
    src/Market/Strategy/Strat_Greedy.hpp \
    src/Market/Strategy/Strat_LinearRegression.hpp \
    src/Market/Strategy/Strat_MovingAverage.hpp \
    src/Utilities/Utilities.hpp \
    src/Protocols/BalancerPool.hpp \
    src/Protocols/ConstantSum.hpp \
    src/Protocols/CurvePool.hpp \
    src/Protocols/Protocols.hpp \
    src/Protocols/UniswapV2Pool.hpp \
    src/Protocols/UniswapV3Pool.hpp \
    src/Playground.hpp \
    src/Market/Infrastructure/Market.hpp \
    src/Market/Infrastructure/CommunityActor.hpp

FORMS += \
    ui/AccountListWidgetItem.ui \
    ui/ArbitrageurSimulationGraphItem.ui \
    ui/ExistingPoolProvisionDialog.ui \
    ui/ManualPlayground.ui \
    ui/MintDialog.ui \
    ui/NewMainWindow.ui \
    ui/NewPoolProvisionDialog.ui \
    ui/PoolGraphItem.ui \
    ui/PoolListWidgetItem.ui \
    ui/PoolTokenDialog.ui \
    ui/PoolTokenListWidgetItem.ui \
    ui/ProvideDialog.ui \
    ui/ProviderSimulationGraphItem.ui \
    ui/SimulationPlayground.ui \
    ui/TokenListWidgetItem.ui \
    ui/TradeDialog.ui \
    ui/WalletListWidgetItem.ui \
    ui/WithdrawDialog.ui \
    ui/introductorywindow.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    LOGO.qrc \
    Logo_background.qrc
