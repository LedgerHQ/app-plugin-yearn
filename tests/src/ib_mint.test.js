import "core-js/stable";
import "regenerator-runtime/runtime";
import { waitForAppScreen, zemu } from './test.fixture';

const BASE_SCREENS_S = (1 + 2 + 1 + 1 + 1) //YEARN + AMOUNT + VAULT + GAS_FEES + APPROVE
const BASE_SCREENS_X = (1 + 1 + 1 + 1 + 1) //YEARN + AMOUNT + VAULT + GAS_FEES + APPROVE

test('[Nano S] IB Mint', zemu("nanos", async (sim, eth) => {
  // Original TX: https://etherscan.io/tx/0xc636b95e390a1f829606fc418b28c7f8a01296742d2d774f3f16c9ca90406bc4
  eth.signTransaction(
    "44'/60'/0'/0/0",
    "02f891016c850a3e9ab800850a3e9ab8008307213094950027632fbd6adadfe82644bfb64647642b6c0980a4a0712d68000000000000000000000000000000000000000000000000000003941e390d81c080a0db490e1d30968e49bd301642af08ff11e8879d89ae7d9dc112346b0a8efcbed1a02beffc76dddc74c691cc7508304c1a206152bb7b60559ea996574f4e6bdd352b"
  );

  await waitForAppScreen(sim);
  await sim.navigateAndCompareSnapshots('.', 'nanos_ib_mint', [BASE_SCREENS_S, 0]);
}));



test('[Nano S] IB Mint', zemu("nanox", async (sim, eth) => {
  // Original TX: https://etherscan.io/tx/0xc636b95e390a1f829606fc418b28c7f8a01296742d2d774f3f16c9ca90406bc4
  eth.signTransaction(
    "44'/60'/0'/0/0",
    "02f891016c850a3e9ab800850a3e9ab8008307213094950027632fbd6adadfe82644bfb64647642b6c0980a4a0712d68000000000000000000000000000000000000000000000000000003941e390d81c080a0db490e1d30968e49bd301642af08ff11e8879d89ae7d9dc112346b0a8efcbed1a02beffc76dddc74c691cc7508304c1a206152bb7b60559ea996574f4e6bdd352b"
  );

  await waitForAppScreen(sim);
  await sim.navigateAndCompareSnapshots('.', 'nanox_ib_mint', [BASE_SCREENS_X, 0]);
}));
