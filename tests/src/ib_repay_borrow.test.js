import "core-js/stable";
import "regenerator-runtime/runtime";
import { waitForAppScreen, zemu } from './test.fixture';

const BASE_SCREENS_S = (1 + 1 + 1 + 1 + 1) //YEARN + AMOUNT + VAULT + GAS_FEES + APPROVE
const BASE_SCREENS_X = (1 + 1 + 1 + 1 + 1) //YEARN + AMOUNT + VAULT + GAS_FEES + APPROVE

test('[Nano S] IB Repay Borrow', zemu("nanos", async (sim, eth) => {
  // Original TX: https://etherscan.io/tx/0x7bbd85e2d3f685f43905b5ad556f5339f1afac36686187e4619f637c60c4c7c3
  eth.signTransaction(
    "44'/60'/0'/0/0",
    "f88b821d99850d8111c4008306cb5394950027632fbd6adadfe82644bfb64647642b6c0980a40e752702000000000000000000000000000000000000000000000000000003f6e2afa50026a0f86a8734ecaf9785c8e4332c1cb1dc0f6a3edc260e461974eaa81248c7b66faaa05ebb38fcdf2ba63b1b862b0c912a2e4123b9bdb55429bb0f0eb3412b4c69c67d"
  );

  await waitForAppScreen(sim);
  await sim.navigateAndCompareSnapshots('.', 'nanos_ib_repay_borrow', [BASE_SCREENS_S, 0]);
}));



test('[Nano S] IB Repay Borrow', zemu("nanox", async (sim, eth) => {
  // Original TX: https://etherscan.io/tx/0x7bbd85e2d3f685f43905b5ad556f5339f1afac36686187e4619f637c60c4c7c3
  eth.signTransaction(
    "44'/60'/0'/0/0",
    "f88b821d99850d8111c4008306cb5394950027632fbd6adadfe82644bfb64647642b6c0980a40e752702000000000000000000000000000000000000000000000000000003f6e2afa50026a0f86a8734ecaf9785c8e4332c1cb1dc0f6a3edc260e461974eaa81248c7b66faaa05ebb38fcdf2ba63b1b862b0c912a2e4123b9bdb55429bb0f0eb3412b4c69c67d"
  );

  await waitForAppScreen(sim);
  await sim.navigateAndCompareSnapshots('.', 'nanox_ib_repay_borrow', [BASE_SCREENS_X, 0]);
}));
