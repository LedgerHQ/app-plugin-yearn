import "core-js/stable";
import "regenerator-runtime/runtime";
import { waitForAppScreen, zemu } from './test.fixture';

const BASE_SCREENS_S = (1 + 2 + 1 + 1 + 1) //YEARN + AMOUNT + VAULT + GAS_FEES + APPROVE
const BASE_SCREENS_X = (1 + 1 + 1 + 1 + 1) //YEARN + AMOUNT + VAULT + GAS_FEES + APPROVE

test('[Nano S] IB Redeem Underlying', zemu("nanos", async (sim, eth) => {
  // Original TX: https://etherscan.io/tx/0x0dfd093bdbd895432dba2e9be2d6ab5c47ec6dfd75611c96f80e811faa7989a1
  eth.signTransaction(
    "44'/60'/0'/0/0",
    "02f891015b85104c533c0085104c533c00830566679441c84c0e2ee0b740cf0d31f63f3b6f627dc6b39380a4852a12e30000000000000000000000000000000000000000000000000de8dda323830c13c001a010d31e41f354a281d70124b5990712529dbc120ebb3c6e6f19101914c37ae82ca03905bf2081babd949ffeea0c3876706a2bd54806af9c9c2ced3417bf9e820558"
  );

  await waitForAppScreen(sim);
  await sim.navigateAndCompareSnapshots('.', 'nanos_ib_redeem_underlying', [BASE_SCREENS_S, 0]);
}));



test('[Nano S] IB Redeem Underlying', zemu("nanox", async (sim, eth) => {
  // Original TX: https://etherscan.io/tx/0x0dfd093bdbd895432dba2e9be2d6ab5c47ec6dfd75611c96f80e811faa7989a1
  eth.signTransaction(
    "44'/60'/0'/0/0",
    "02f891015b85104c533c0085104c533c00830566679441c84c0e2ee0b740cf0d31f63f3b6f627dc6b39380a4852a12e30000000000000000000000000000000000000000000000000de8dda323830c13c001a010d31e41f354a281d70124b5990712529dbc120ebb3c6e6f19101914c37ae82ca03905bf2081babd949ffeea0c3876706a2bd54806af9c9c2ced3417bf9e820558"
  );

  await waitForAppScreen(sim);
  await sim.navigateAndCompareSnapshots('.', 'nanox_ib_redeem_underlying', [BASE_SCREENS_X, 0]);
}));
