import "core-js/stable";
import "regenerator-runtime/runtime";
import { waitForAppScreen, zemu } from './test.fixture';

const BASE_SCREENS_S = (1 + 1 + 3 + 1 + 1) //YEARN + AMOUNT + GAS_FEES + VAULT + APPROVE
const BASE_SCREENS_X = (1 + 1 + 1 + 1 + 1) //YEARN + AMOUNT + GAS_FEES + VAULT + APPROVE

// Nanos S test
test('[Nano S] Exit Lab Pickle', zemu("nanos", async (sim, eth) => {
  // Original TX: https://etherscan.io/tx/0xf0e90e479fd0b1dbac0d4a334d5d75e59bdde1104250db460ed1c024517cc1ee
  eth.signTransaction(
    "44'/60'/0'/0/0",
    "02f872018201828459682f00852e8f2604d6830344ff94da481b277dce305b97f4091bd66595d57cf316348084e9fad8eec001a0e0f96be754984cdb48dab5325c56e037f8447fdbbb904a88d8976fbeb694460aa03087b4d1a8f1eb7e691c19458ac613fa00a541e7ab4b21bceef1feb20a1ec6b6"
  );

  await waitForAppScreen(sim);
  await sim.navigateAndCompareSnapshots('.', 'nanos_exit_pickle', [BASE_SCREENS_S, 0]);
}));

test('[Nano X] Exit Lab Pickle', zemu("nanox", async (sim, eth) => {
  // Original TX: https://etherscan.io/tx/0xf0e90e479fd0b1dbac0d4a334d5d75e59bdde1104250db460ed1c024517cc1ee
  eth.signTransaction(
    "44'/60'/0'/0/0",
    "02f872018201828459682f00852e8f2604d6830344ff94da481b277dce305b97f4091bd66595d57cf316348084e9fad8eec001a0e0f96be754984cdb48dab5325c56e037f8447fdbbb904a88d8976fbeb694460aa03087b4d1a8f1eb7e691c19458ac613fa00a541e7ab4b21bceef1feb20a1ec6b6"
  );

  await waitForAppScreen(sim);
  await sim.navigateAndCompareSnapshots('.', 'nanox_exit_pickle', [BASE_SCREENS_X, 0]);
}));
