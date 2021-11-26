import "core-js/stable";
import "regenerator-runtime/runtime";
import { waitForAppScreen, zemu, genericTx } from './test.fixture';
import { ethers } from "ethers";

const contractAddr = "0x950027632fbd6adadfe82644bfb64647642b6c09";
const AMOUNT_TO_REPAY = '4358900000000';
const BASE_SCREENS_S = (1 + 1 + 1 + 1 + 1) //YEARN + AMOUNT + GAS_FEES + VAULT + APPROVE
const BASE_SCREENS_X = (1 + 1 + 1 + 1 + 1) //YEARN + AMOUNT + GAS_FEES + VAULT + APPROVE

// Nanos S test
test('[Nano S] IB Repay Borrow', zemu("nanos", async (sim, eth) => {
  const contract = new ethers.Contract(contractAddr, ['function repayBorrow(uint256 repayAmount)']);
  const {data} = await contract.populateTransaction.repayBorrow(AMOUNT_TO_REPAY);
  let unsignedTx = genericTx;
  unsignedTx.to = contractAddr;
  unsignedTx.data = data;

  const serializedTx = ethers.utils.serializeTransaction(unsignedTx).slice(2);
  const tx = eth.signTransaction("44'/60'/0'/0", serializedTx);

  await waitForAppScreen(sim);
  await sim.navigateAndCompareSnapshots('.', 'nanos_ib_borrow', [BASE_SCREENS_S, 0]);
  await tx;
}));

test('[Nano X] IB Repay Borrow', zemu("nanox", async (sim, eth) => {
  const contract = new ethers.Contract(contractAddr, ['function repayBorrow(uint256 repayAmount)']);
  const {data} = await contract.populateTransaction.repayBorrow(AMOUNT_TO_REPAY);
  let unsignedTx = genericTx;
  unsignedTx.to = contractAddr;
  unsignedTx.data = data;

  const serializedTx = ethers.utils.serializeTransaction(unsignedTx).slice(2);
  const tx = eth.signTransaction("44'/60'/0'/0", serializedTx);

  await waitForAppScreen(sim);
  await sim.navigateAndCompareSnapshots('.', 'nanox_ib_borrow', [BASE_SCREENS_X, 0]);
  await tx;
}));