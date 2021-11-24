import "core-js/stable";
import "regenerator-runtime/runtime";
import { waitForAppScreen, zemu } from './test.fixture';

const BASE_SCREENS_S = (1 + 1 + 1 + 1 + 1 + 1) //YEARN + AMOUNT + VAULT + NETWORK + GAS_FEES + APPROVE
const BASE_SCREENS_X = (1 + 1 + 1 + 1 + 1 + 1) //YEARN + AMOUNT + VAULT + NETWORK + GAS_FEES + APPROVE

test('[Nano S] IB Borrow', zemu("nanos", async (sim, eth) => {
  // Original TX: https://etherscan.io/tx/0xc7033601b74355ea93d4fc6ca0b01507f8bd54afefdedd8e534fd1b1657f236b
  eth.signTransaction(
    "44'/60'/0'/0/0",
    "f88b821d938511ed8ec200830c076894950027632fbd6adadfe82644bfb64647642b6c0980a4c5ebeaec000000000000000000000000000000000000000000000000000003f6e2afa50026a03a4830cc8db3c3f95ac6b1859cb8671a9665936fcae065c41c12df930c630175a03b9048cfc1efdc309ce2a44fd463e340ce6e498e04f02cd2aa0482fa3d32fa42"
  );

  await waitForAppScreen(sim);
  await sim.navigateAndCompareSnapshots('.', 'nanos_ib_borrow', [BASE_SCREENS_S, 0]);
}));



test('[Nano S] IB Borrow', zemu("nanox", async (sim, eth) => {
  // Original TX: https://etherscan.io/tx/0xc7033601b74355ea93d4fc6ca0b01507f8bd54afefdedd8e534fd1b1657f236b
  eth.signTransaction(
    "44'/60'/0'/0/0",
    "f88b821d938511ed8ec200830c076894950027632fbd6adadfe82644bfb64647642b6c0980a4c5ebeaec000000000000000000000000000000000000000000000000000003f6e2afa50026a03a4830cc8db3c3f95ac6b1859cb8671a9665936fcae065c41c12df930c630175a03b9048cfc1efdc309ce2a44fd463e340ce6e498e04f02cd2aa0482fa3d32fa42"
  );

  await waitForAppScreen(sim);
  await sim.navigateAndCompareSnapshots('.', 'nanox_ib_borrow', [BASE_SCREENS_X, 0]);
}));
