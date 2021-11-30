import "core-js/stable";
import "regenerator-runtime/runtime";
import { waitForAppScreen, zemu } from './test.fixture';

const BASE_SCREENS_S = (1 + 1 + 2 + 1 + 1) //YEARN + AMOUNT + GAS_FEES + VAULT + APPROVE
const BASE_SCREENS_X = (1 + 1 + 1 + 1 + 1) //YEARN + AMOUNT + GAS_FEES + VAULT + APPROVE

// Nanos S test
test('[Nano S] Get Rewards Lab Pickle', zemu("nanos", async (sim, eth) => {
  // Original TX: https://etherscan.io/tx/0x00599bb73397144451412802241e50eddb5592e873018f37bc872ca76b9c43db
  eth.signTransaction(
    "44'/60'/0'/0/0",
    "02f872018201c88459682f00850fd51da8008301eb7b94da481b277dce305b97f4091bd66595d57cf3163480843d18b912c080a07eb7ba3c618b0dec556390f547a547d219d499b64552435d04ee2df9dab3b8e4a01c5cb0907a679d54d7519c09b3cfaaaa8ff887c2a209f65753d7f5972d57e3fa"
  );

  await waitForAppScreen(sim);
  await sim.navigateAndCompareSnapshots('.', 'nanos_getRewards_pickle', [BASE_SCREENS_S, 0]);
  await tx;
}));

test('[Nano X] Get Rewards Lab Pickle', zemu("nanox", async (sim, eth) => {
  // Original TX: https://etherscan.io/tx/0x00599bb73397144451412802241e50eddb5592e873018f37bc872ca76b9c43db
  eth.signTransaction(
    "44'/60'/0'/0/0",
    "02f872018201c88459682f00850fd51da8008301eb7b94da481b277dce305b97f4091bd66595d57cf3163480843d18b912c080a07eb7ba3c618b0dec556390f547a547d219d499b64552435d04ee2df9dab3b8e4a01c5cb0907a679d54d7519c09b3cfaaaa8ff887c2a209f65753d7f5972d57e3fa"
  );

  await waitForAppScreen(sim);
  await sim.navigateAndCompareSnapshots('.', 'nanox_getRewards_pickle', [BASE_SCREENS_X, 0]);
  await tx;
}));
